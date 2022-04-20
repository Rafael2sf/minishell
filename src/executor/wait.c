/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:41:53 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 18:40:00 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	tk_wait(t_ast *tk, void *p)
{
	t_mshell	*shell;

	shell = (t_mshell *)p;
	call_sigact(SI_IGN, shell);
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
