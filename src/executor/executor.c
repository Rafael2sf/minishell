/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/19 12:30:53 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

static int	check_parameter(char **input)
{
	int	i;

	i = 0;
	while (ft_is(input[1][i], " \t"))
		i++;
	if (ft_is(input[1][i], "-+"))
		i++;
	while (input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i++]) || i == 20)
			return (-1);
	}
	return (0);
}

int	ms_valid_exit(t_ast *tokens)
{
	char		**data;

	data = (char **)(tokens->data);
	return (tokens->type == E_CMD && data && ft_strncmp(data[0], "exit", 5) == 0
		&& (!data[1] || (data[1] && !data[2]) || check_parameter(data) == -1));
}

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
				// If command is not valid close pipe
				if (tk->func == ft_cd || tk->func == ft_unset
					|| tk->func == ft_exit || ((tk->func) == ft_export
						&& ((char **)(tk->data))[1] != NULL))
				{
					close((tk->p)[1]);
					return (0);
				}
			}
			// if valid exit free mem and exit
			if (ms_valid_exit(tk))
				ms_exit(shell);
			// run valid function
			(shell->stat) = (tk->func)((char **)(tk->data),
					(tk->p)[1], &(shell->stat), &(shell->env));
			return (0);
		}
		// else run binary in child process
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
			ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
			execve(((char **)tk->data)[0], (char **)(tk->data), (shell->env));
			ptr_ptr_free((void **)(shell->env));
			ast_free(&shell->tokens);
			clear_history();
			exit(0);
		}
	}
	return (0);
}

int	tk_wait(t_ast *tk, void *p)
{
	t_mshell			*shell;

	shell = (t_mshell *)p;
	if (call_sigact('i') == -1)
		return (errno);
	if (tk->type == E_CMD)
	{
		if (!tk->prev || (tk->prev->right == tk && !tk->prev->prev))
		{
			waitpid(tk->pid, &(shell->stat), 0);
			if (WIFSIGNALED(shell->stat))
			{
				(shell->stat) += 128;
				if ((shell->stat) == 130)
					ft_putchar_fd('\n', STDOUT_FILENO);
				if ((shell->stat) == 131)
					ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
			}
			else
				(shell->stat) = WEXITSTATUS(shell->stat);
		}
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
		ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
	}
	else
	{
		if (call_sigact('d') == -1)
			return (errno);
		ast_iter_in(shell->tokens, tk_exec, 0, (void *)(shell));
		ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
		ast_iter_in(shell->tokens, tk_wait, 1, (void *)(shell));
	}
	return (0);
}
