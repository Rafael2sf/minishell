/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:55:02 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:44:35 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

int	get_total(char **env)
{
	int	i;
	int	j;
	int	total;

	total = 0;
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
			j++;
		total += j;
		i++;
	}
	return (total);
}

char	**sort_env_cpy(char **env_cpy, int total)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_cpy[i] != NULL)
	{
		j = i + 1;
		while (env_cpy[j] != NULL)
		{
			if (ft_strncmp(env_cpy[i], env_cpy[j], total) > 0)
			{
				tmp = env_cpy[i];
				env_cpy[i] = env_cpy[j];
				env_cpy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env_cpy);
}
