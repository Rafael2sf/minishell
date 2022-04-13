/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/11 16:43:46 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

/*
int	ms_exec_builtin(t_ast *tk, t_mshell *shell)
{
	close((tk->p[0]));
	if (ft_strncmp(((char **)(tk->data))[0], "exit", 5) == 0)
		return (ft_exit((char **)(tk->data), (tk->p)[1], *(shell->env), &shell->stat));
	else if (ft_strncmp(((char **)(tk->data))[0], "cd", 3) == 0)
		return (ft_cd((char **)(tk->data), (tk->p)[1], (shell->env)));
	else if (ft_strncmp(((char **)(tk->data))[0], "echo", 5) == 0)
		return (ft_echo((char **)(tk->data), (tk->p)[1]));
	else if (ft_strncmp(((char **)(tk->data))[0], "env", 4) == 0)
		return (ft_env((char **)(tk->data), (tk->p)[1], *(shell->env)));
	else if (ft_strncmp(((char **)(tk->data))[0], "export", 7) == 0)
		return (ft_export((char **)(tk->data), (tk->p)[1], (shell->env)));
	else if (ft_strncmp(((char **)(tk->data))[0], "unset", 6) == 0)
		return (ft_unset((char **)(tk->data), (tk->p)[1], (shell->env)));
	else if (ft_strncmp(((char **)(tk->data))[0], "pwd", 4) == 0)
		return (ft_pwd((char **)(tk->data), (tk->p)[1], *(shell->env)));
	return (-1);
}
*/

int	tk_close_all(t_ast *tk, void *p)
{
	(void)(p);
	if (!tk)
		return (0);
	if (tk->type == E_CMD || tk->type == E_UNDEF)
	{
		if ((tk->p)[0] > 2)
			close((tk->p)[0]);
		if ((tk->p)[1] > 2)
			close((tk->p)[1]);
	}
	return (0);
}

int	tk_exec(t_ast *tk, void *p)
{
	t_mshell	*shell;
	struct sigaction	act;

	if (!tk)
		return (0);
	shell = (t_mshell *)p;
	if (tk->type == E_CMD)
	{
		if (tk->func)
		{
			close((tk->p)[0]);
			if (tk->prev)
			{
				if (tk->func == ft_cd || tk->func == ft_unset || tk->func == ft_exit
					|| ((tk->func) == ft_export && ((char **)(tk->data))[1] != NULL))
				{
					close((tk->p)[1]);
					return (0);
				}
			}
			(tk->func)((char **)(tk->data),(tk->p)[1], &(shell->stat), (shell->env));
			return (0);
		}

		(tk->pid) = fork();
		if (tk->pid == -1)
		{
			perror("minishell: ");
			return (1);
		}

		if (tk->pid == 0)
		{
			dup2((tk->p)[0], STDIN_FILENO);
			dup2((tk->p)[1], STDOUT_FILENO);
			ast_iter_pre(shell->tokens, tk_close_all, 0, NULL);
			execve(((char **)tk->data)[0], (char **)(tk->data), *(shell->env));
			ptr_ptr_free((void **)(shell->env));
			ast_free(&shell->tokens);
			exit(0);
		}
	}
	prep_act(&act, 'h');
	if (sigaction(SIGINT, &act, NULL) == -1 ||
        sigaction(SIGQUIT, &act, NULL) == -1)
    {
       	perror("Error in sigaction");
        return (errno);
	}
	return (0);
}

int	tk_wait(t_ast *tk, void *p)
{
	t_mshell		*shell;

	shell = (t_mshell *)p;
	if (tk->type == E_CMD)
	{
		if (!tk->prev || (tk->prev->right == tk && !tk->prev->prev))
			waitpid(tk->pid, &(shell->stat), 0);
		else
			waitpid(tk->pid, NULL, 0);
	}
	return (0);
}

int	ms_executor(t_mshell *shell)
{
	if (DEBUG)
	{
		printf("\n\t <-- PARSER --> \n");
		ast_print(shell->tokens, 0, 1);
		ast_iter_pre(shell->tokens, tk_close_all, 0, NULL);
	}
	else
	{
		ast_iter_in(shell->tokens, tk_exec, 0, (void *)(shell));
		ast_iter_pre(shell->tokens, tk_close_all, 0, NULL);
		ast_iter_in(shell->tokens, tk_wait, 1, (void *)(shell));
	}
	return (0);
}
