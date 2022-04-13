/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:11:42 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/13 11:42:30 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ms_exit(t_mshell *shell)
{
	char		*cmd[3];
	int			val;
	char		**data;
	
	data = NULL;
	if (shell->tokens)
		data = (char **)(shell->tokens->data);
	cmd[0] = "exit";
	cmd[2] = NULL;
	if (data && data[1])
	{
		val = ft_atoi(data[1]);
		cmd[1] = ft_strdup(data[1]);
	}
	else
	{
		val = (shell->stat);
		cmd[1] = NULL;
	}
	ptr_ptr_free((void **)(*shell->env));
	ast_free(&(shell->tokens));
	ft_exit(cmd, -1, &val, NULL);
}