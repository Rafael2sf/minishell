/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:30:16 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/31 16:30:43 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

char	**creat_copy(char **env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	while (env[i] != NULL)
		i++;
	env_cpy = malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		env_cpy[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!env_cpy[i])
		{
			ptr_ptr_free((void **)env_cpy);
			return (NULL);
		}
		ft_strlcpy(env_cpy[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
