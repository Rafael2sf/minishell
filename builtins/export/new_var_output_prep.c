/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_output_prep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:57:47 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:57:57 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	*find_var_exp(char **env, int name_variable_index,
		char **split_input)
{
	int		i;
	char	*equal_ptr;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], *split_input, name_variable_index + 1))
			return (env[i]);
		i++;
	}
	i = 0;
	if (ft_strchr(*split_input, '\"') != NULL)
	{
		while ((*split_input)[i] != '\0')
		{
			if ((*split_input)[i] == '\"')
				(*split_input)[i] = '\'';
			i++;
		}
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

char	**prep_output(char *split_input, char **env, int name_variable_index)
{	
	int		j;
	int		i;
	char	*equal_ptr;
	char	*existing_var;

	i = ft_strlen(split_input);
	equal_ptr = ft_strchr(split_input, '=');
	if (equal_ptr == NULL)
		i += 3;
	if (equal_ptr != NULL && equal_ptr[1] == '\0')
		i += 2;
	existing_var = find_var_exp(env, name_variable_index, &split_input);
	j = 0;
	while (env[j] != NULL && env[j] != existing_var)
		j++;
	if (set_new_var(&env, existing_var, i, j) == NULL)
		return (NULL);
	ft_strlcpy(env[j], split_input, i + 1);
	if (equal_ptr == NULL)
		ft_strlcat(env[j], "=\'\'", i + 1);
	else if (equal_ptr != NULL && equal_ptr[1] == '\0')
		ft_strlcat(env[j], "\'\'", i + 1);
	return (env);
}
