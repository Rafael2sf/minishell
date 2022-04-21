/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:52:11 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 11:26:23 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	tk_close_all(t_ast *tk, void *p);

void	ms_clean(t_mshell *shell)
{
	if (!shell)
		return ;
	if (shell->prompt)
		free(shell->prompt);
	if (shell->env)
		ptr_ptr_free((shell->env));
	if (shell->tokens)
	{
		ast_iter_pre(shell->tokens, tk_close_all, 0, (void *)(shell));
		ast_free(&shell->tokens);
	}
	clear_history();
}

void	werror(char *s)
{
	if (s)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		perror(s);
	}
	else
		perror("minishell");
}
