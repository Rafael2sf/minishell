/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:26:10 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/15 15:52:21 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "main.h"

static char	**export_at_start_process(char ***env);
static void	reset_oldpwd(char **env);
static char	*alloc_new_lvl(char *ptr, char *old_shlvl);
static char	**change_shlvl(char ***env);

char	**ms_init_env(char **envp)
{
	char	**env_cpy;

	env_cpy = ptr_ptr_dup(envp);
	if (!env_cpy)
	{
		perror("minishell: error creating env");
		return (NULL);
	}
	change_shlvl(&env_cpy);
	if (!env_cpy)
		return (NULL);
	env_cpy = export_at_start_process(&env_cpy);
	return (env_cpy);
}

static char	**export_at_start_process(char ***env)
{
	char	*input[3];
	int		i;

	input[0] = "unset";
	input[2] = NULL;
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strchr((*env)[i], '=') == NULL
			&& ft_strncmp((*env)[i], "OLDPWD", 6) != 0)
		{
			input[1] = (*env)[i];
			ft_unset(input, 1, NULL, env);
			if ((*env)[i] == NULL)
				break ;
			continue ;
		}
		i++;
	}
	reset_oldpwd(*env);
	return (*env);
}

static void	reset_oldpwd(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			tmp = ft_strdup("OLDPWD");
			if (tmp)
			{
				free(env[i]);
				env[i] = tmp;
				break ;
			}
			else
			{
				perror("");
				return ;
			}
		}
		i++;
	}
}

static char	**change_shlvl(char ***env)
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

static char	*alloc_new_lvl(char *ptr, char *old_shlvl)
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
