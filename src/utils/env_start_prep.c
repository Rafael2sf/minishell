/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_start_prep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:37:53 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:40:46 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"

char	**reset_oldpwd(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			ft_bzero(env[i], ft_strlen(env[i]));
			ft_strlcpy(env[i], "OLDPWD", 7);
		}
		i++;
	}
	return (env);
}

char	**export_at_start_process(char **env)
{
	char	*input[3];
	int		i;

	input[0] = "unset";
	input[2] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') == NULL)
		{
			input[1] = env[i];
			ft_unset(input, 1, &env);
			continue ;
		}
		i++;
	}
	env = reset_oldpwd(env);
	return (env);
}
