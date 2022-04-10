/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:48:40 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/06 11:26:00 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static char	*find_var_unset(char **env, int n_v_index, char *input);
static int	prep_output_unset(char *input, char ***env, int n_v_index);
static int	set_var_unset(char ***env, char **input);

int	ft_unset(char **input, int fd, int *stat, char ***env)
{
	(void)(stat);
	close(fd);
	if (!*env)
	{
		ft_putendl_fd("error: env is empity", 2);
		return (1);
	}
	if (!input[1])
		return (0);
	return (set_var_unset(env, input));
}

static char	*find_var_unset(char **env, int n_v_index, char *input)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], input, n_v_index)
			&& (env[i][n_v_index] == '=' || env[i][n_v_index] == '\0'))
			return (env[i]);
		i++;
	}
	return (NULL);
}

static int	prep_output_unset(char *input, char ***env, int n_v_index)
{	
	int		i;
	char	*existing_var;

	i = 0;
	existing_var = find_var_unset(*env, n_v_index, input);
	if (!existing_var)
		return (0);
	while ((*env)[i] != NULL)
		i++;
	*env = ft_realloc_unset(env, i, existing_var);
	if (*env == NULL)
		return (errno);
	return (0);
}

static int	set_var_unset(char ***env, char **input)
{
	int	n_v_index;
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (input[i] != NULL)
	{
		n_v_index = parsing_input_name_unset(&input[i]);
		if (!n_v_index)
		{
			i++;
			ret = 1;
			continue ;
		}
		if (prep_output_unset(input[i++], env, n_v_index))
			return (errno);
	}
	return (ret);
}
