/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/08 18:33:14 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/executor.h"
#include "../../headers/builtins.h"

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

int	ms_is_builtin(const char *s)
{
	if (ft_strncmp(s, "exit", 5) == 0)
		return (0);
	else if (ft_strncmp(s, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(s, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(s, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(s, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(s, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(s, "pwd", 4) == 0)
		return (0);
	return (-1);
}

int	tk_prep(t_ast *tk, void *p)
{
	if (tk->type == E_PIPE)
	{
		if (pipe(tk->p) == -1)
			return (-1);
	}
	else if (tk->type == E_CMD)
	{
		(tk->p[0]) = ms_get_input(tk);
		if (tk->p[0] == -1)
		{
			ft_free_m((char **)tk->data);
			(tk->type) = E_UNDEF;
			return (1);
		}
		(tk->p[1]) = ms_get_output(tk);
		if (tk->p[1] == -1)
		{
			ft_free_m((char **)tk->data);
			(tk->type) = E_UNDEF;
			return (1);
		}
		if (ms_is_builtin(((char **)tk->data)[0]) == 0)
			return (0) ;
		if (!ms_newcmd(&((char **)tk->data)[0], (char **)(p)))
		{
			ft_free_m((char **)tk->data);
			(tk->type) = E_UNDEF;
			return (1);
		}
	}
	return (0);
}

int	tk_exec(t_ast *tk, void *p)
{
	t_mshell	*shell;

	shell = (t_mshell *)p;
	if (tk->type == E_CMD)
	{
		if (ms_exec_builtin(tk, shell) != -1)
			return (0);
		(tk->pid) = fork();
		if (tk->pid == -1)
		{
			perror("minishell:");
			return (1);
		}
		if (tk->pid == 0)
		{
			dup2((tk->p)[0], STDIN_FILENO);
			dup2((tk->p)[1], STDOUT_FILENO);
			close((tk->p)[0]);
			close((tk->p)[1]);
			execve(((char **)tk->data)[0], (char **)(tk->data), *(shell->env));
			printf("--- execve error ---- \n");
			exit(0);
		}
		else
		{
			close((tk->p)[0]);
			close((tk->p)[1]);
		}
	}
	else if (tk->type == E_UNDEF)
	{
		close((tk->p)[0]);
		close((tk->p)[1]);
	}
	return (0);
}

int	tk_wait(t_ast *tk, void *p)
{
	t_mshell		*shell;

	shell = (t_mshell *)p;
	if (tk->type == E_CMD)
	{
		if (!tk->prev || (tk->prev->right == tk && !tk->prev->prev)) // if last
			waitpid(tk->pid, &(shell->stat), 0);
		else
			wait(0);
	}
	return (0);
}

int	ast_executor(t_mshell *shell)
{
	char	**paths;
	int		state;
	
	paths = ms_paths();
	state = ast_iter_pre(shell->tokens, tk_prep, 0, (void *)(paths));
	ft_free_m(paths);
	if (DEBUG)
		ast_print(shell->tokens, 0);
	else
	{
		ast_iter_in(shell->tokens, tk_exec, 0, (void *)(shell));
		ast_iter_in(shell->tokens, tk_wait, 1, (void *)(shell));
	}
	return (state);
}
