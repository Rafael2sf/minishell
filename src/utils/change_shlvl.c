/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:26:10 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:40:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*alloc_new_lvl(char *ptr, char *old_shlvl)
{
	free((old_shlvl));
	old_shlvl = ft_strjoin("SHLVL=", ptr);
	free(ptr);
	if (!old_shlvl)
	{
		perror("error allocating SHLVL");
		return (NULL);
	}
	return (old_shlvl);
}

char	**change_shlvl(char ***env)
{
	int		i;
	int		lvl;
	char	*ptr;

	i = 0;
	while ((*env)[i] != NULL && ft_strncmp("SHLVL=", (*env)[i], 6) != 0)
		i++;
	if (!(*env)[i])
		return (NULL);
	ptr = ft_strchr((*env)[i], '=');
	if (!ptr)
		return (NULL);
	lvl = ft_atoi(++ptr);
	lvl++;
	ptr = ft_itoa(lvl);
	if (!ptr)
	{
		perror("error allocating SHLVL");
		return (NULL);
	}
	(*env)[i] = alloc_new_lvl(ptr, (*env)[i]);
	if (!(*env)[i])
		return (NULL);
	return (*env);
}
