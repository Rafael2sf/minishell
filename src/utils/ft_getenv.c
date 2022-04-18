/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:08 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/18 11:01:37 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_getenv(char *env_var, char **env)
{
	int		i;
	int		len;

	i = 0;
	if (!env_var)
		return (NULL);
	len = ft_strlen(env_var);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env_var, env[i], len) == 0)
		{
			if (env[i][len] == '=')
				return (&(env[i][++len]));
			else if (env[i][len] == '\0')
				return (&(env[i][len]));
		}
		i++;
	}
	return (NULL);
}
