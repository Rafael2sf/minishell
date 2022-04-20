/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:52:11 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 11:38:33 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ms_clean(t_mshell *shell)
{
	if (!shell)
		return ;
	if (shell->prompt)
		free(shell->prompt);
	if (shell->env)
		ptr_ptr_free((void **)(shell->env));
	if (shell->tokens) // CLOSE FILES
		ast_free(&shell->tokens);
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
