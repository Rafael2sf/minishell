/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:55:02 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:45 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

void	ptr_ptr_free(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free (ptr[i++]);
	free(ptr);
}

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
