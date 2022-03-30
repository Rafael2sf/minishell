/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:48:40 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/30 12:05:37 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	*find_var_unset(char **env, int n_v_index, char *input)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], input, n_v_index)
			&& env[i][n_v_index] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**prep_output_unset(char *input, char **env, int n_v_index)
{	
	int		i;
	char	*existing_var;

	i = 0;
	existing_var = find_var_unset(env, n_v_index, input);
	if (!existing_var)
		return (env);
	while (env[i] != NULL)
		i++;
	if (ft_realloc_unset(&env, i, existing_var) == NULL)
		return (NULL);
	return (env);
}

char	**set_var_unset(char **env, char **input)
{
	int	n_v_index;
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		n_v_index = parsing_input_name_unset(&input[i]);
		if (!n_v_index)
		{
			i++;
			continue ;
		}
		env = prep_output_unset(input[i++], env, n_v_index);
		if (!env)
			return (NULL);
	}
	return (env);
}

char	**ft_unset(char **input, int fd, char **env) //Fd???????????
{
	if (!env)
	{
		ft_putendl_fd("error: env does not exist", 2);
		return (NULL);
	}
	if (!input[1] || input[1][0] == '\0')
		return (env);
	env = set_var_unset(env, input);
	return (env);
}
