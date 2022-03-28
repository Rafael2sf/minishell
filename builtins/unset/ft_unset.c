/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:48:40 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:42:26 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	*find_var_unset(char **env, int n_v_index, char *split_input)
{
	int		i;
	int		j;
	char	*equal_ptr;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], split_input, n_v_index)
			&& env[i][n_v_index] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**prep_output_unset(char *split_input, char **env, int n_v_index)
{	
	int		i;
	char	*equal_ptr;
	char	*existing_var;

	i = 0;
	existing_var = find_var_unset(env, n_v_index, split_input);
	if (!existing_var)
		return (env);
	while (env[i] != NULL)
		i++;
	if (ft_realloc_unset(&env, i, existing_var) == NULL)
		return (NULL);
	return (env);
}

char	**real_set_var_unset(char **env, char **split_input, int *error_count)
{
	int	n_v_index;
	int	i;

	i = 0;
	while (split_input[i] != NULL)
	{
		n_v_index = parsing_input_name_unset(&split_input[i], error_count);
		if (!n_v_index)
		{
			i++;
			continue ;
		}
		env = prep_output_unset(split_input[i++], env, n_v_index);
		if (!env)
			return (NULL);
	}
	return (env);
}

static char	**set_variables_unset(char *input, char **env)
{
	char		**split_input;
	static int	error_count = 0;

	split_input = altered_split(input, ' ');
	if (!split_input)
	{
		perror("Error splitting input");
		return (NULL);
	}
	env = real_set_var_unset(env, split_input, &error_count);
	ptr_ptr_free((void **) split_input);
	error_count = 0;
	return (env);
}

char	**ft_unset(char *input, int fd, char **env)
{
	int	i;

	if (!env)
	{
		ft_putendl_fd("error: env does not exist", 2);
		return (NULL);
	}
	if (!input || input[0] == '\0')
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (env);
	}
	env = set_variables_unset(input, env);
	return (env);
}
