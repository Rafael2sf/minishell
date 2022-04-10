/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:30:00 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/10 17:30:01 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

t_bultinf	ms_find_builtin(const char *s)
{
	if (ft_strncmp(s, "exit", 5) == 0)
		return (&ft_exit);
	else if (ft_strncmp(s, "cd", 3) == 0)
		return (&ft_cd);
	else if (ft_strncmp(s, "echo", 5) == 0)
		return (&ft_echo);
	else if (ft_strncmp(s, "env", 4) == 0)
		return (&ft_env);
	else if (ft_strncmp(s, "export", 7) == 0)
		return (&ft_export);
	else if (ft_strncmp(s, "unset", 6) == 0)
		return (&ft_unset);
	else if (ft_strncmp(s, "pwd", 4) == 0)
		return (&ft_pwd);
	return (NULL);
}
