/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:39:56 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 18:29:06 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	ms_exec_builtin(t_ast *tk, t_mshell *shell);
static int	ms_exec_child(t_ast *tk, t_mshell *shell);

int	tk_exec(t_ast *tk, void *p)
{
	t_mshell	*shell;

	if (!tk)
		return (0);
	shell = (t_mshell *)p;
	if (tk->type == E_CMD)
	{
		if (tk->func && ms_exec_builtin(tk, shell) == 0)
			return (0);
		(tk->pid) = fork();
		if (tk->pid == -1)
		{
			werror(NULL);
			(shell->stat) = errno;
			return (-1);
		}
		if (tk->pid == 0)
			ms_exec_child(tk, shell);
	}
	return (0);
}

static int	ms_exec_builtin(t_ast *tk, t_mshell *shell)
{
	if ((tk->p)[0] > 2)
		close((tk->p)[0]);
	if (tk->prev)
	{
		if (tk->func == ft_cd || tk->func == ft_unset
			|| tk->func == ft_exit || ((tk->func) == ft_export
				&& ((char **)(tk->data))[1] != NULL))
		{
			if ((tk->p)[1] > 2)
				close((tk->p)[1]);
			(shell->stat) = 1;
			return (0);
		}
		(shell->stat) = (tk->func)((char **)(tk->data),
				(tk->p)[1], &(shell->stat), &(shell->env));
		return (0);
	}
	if (ms_valid_exit(tk))
		ms_exit(shell);
	(shell->stat) = (tk->func)((char **)(tk->data),
			(tk->p)[1], &(shell->stat), &(shell->env));
	return (0);
}

static int	ms_exec_child(t_ast *tk, t_mshell *shell)
{
	if (dup2((tk->p)[0], STDIN_FILENO) != -1)
	{
		if (dup2((tk->p)[1], STDOUT_FILENO) != -1)
		{
			ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
			execve(((char **)tk->data)[0], (char **)(tk->data), (shell->env));
		}
	}
	werror(NULL);
	ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
	ms_clean(shell);
	exit(0);
}
