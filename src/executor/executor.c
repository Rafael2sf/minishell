/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 14:31:39 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

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
		call_sigact(SI_DFL, shell);
		ast_iter_in(shell->tokens, tk_exec, 0, (void *)(shell));
		ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
		ast_iter_in(shell->tokens, tk_wait, 1, (void *)(shell));
	}
	return (0);
}
