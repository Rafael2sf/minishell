/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_output_prep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:57:47 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/30 10:36:04 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	*find_var_exp(char **env, int name_variable_index,
		char **split_input)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], *split_input, name_variable_index + 1))
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	**set_new_var(char ***env, char *existing_var, int i, int j)
{
	if (!existing_var)
	{
		if (ft_realloc(env, sizeof(char *) * (j + 2)) == NULL)
			return (NULL);
		(*env)[j + 1] = NULL;
	}
	else
		free((*env)[j]);
	(*env)[j] = malloc(sizeof(char) * (i + 1));
	if (!(*env)[j])
	{
		perror("Error allocating variable");
		return (NULL);
	}
	return (*env);
}

char	**prep_output(char *input, char **env, int name_variable_index)
{	
	int		j;
	int		i;
	char	*equal_ptr;
	char	*existing_var;

	i = ft_strlen(input);
	equal_ptr = ft_strchr(input, '=');
	if (equal_ptr != NULL && equal_ptr[1] == '\0')
		i += 2;
	existing_var = find_var_exp(env, name_variable_index, &input);
	j = 0;
	while (env[j] != NULL && env[j] != existing_var)
		j++;
	if (set_new_var(&env, existing_var, i, j) == NULL)
		return (NULL);
	ft_strlcpy(env[j], input, i + 1);
	return (env);
}
