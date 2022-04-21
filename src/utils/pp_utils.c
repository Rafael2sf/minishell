/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:28:35 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 12:44:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ptr_ptr_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
}

int	ptr_ptr_len(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	**ptr_ptr_join(char **a, char **b)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	if (!a && !b)
		return (NULL);
	len = ptr_ptr_len(a) + ptr_ptr_len(b);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (a && a[j])
		new[i++] = a[j++];
	j = 0;
	while (b && b[j])
		new[i++] = b[j++];
	new[i] = NULL;
	if (a)
		free(a);
	if (b)
		free(b);
	return (new);
}

char	**ptr_ptr_dup(char **env)
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
			while (--i > 0)
				free(env_cpy[i]);
			ptr_ptr_free(env_cpy);
			return (NULL);
		}
		ft_strlcpy(env_cpy[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
