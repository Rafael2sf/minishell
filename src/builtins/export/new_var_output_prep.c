/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_output_prep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:57:47 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:34 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

static char	*find_var_exp(char **env, int name_variable_index,
		char **split_input)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], *split_input, name_variable_index))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**set_new_var(char **env, char *existing_var, int i, int j)
{
	if (!existing_var)
	{
		if (ft_realloc(&env, sizeof(char *) * (j + 2)) == NULL)
			return (0);
		env[j + 1] = NULL;
	}
	else
		free(env[j]);
	env[j] = malloc(sizeof(char) * (i + 1));
	if (!env[j])
	{
		perror("Error allocating variable");
		return (NULL);
	}
	return (env);
}

char	**prep_output(char *input, char **env, int name_variable_index)
{	
	int		j;
	int		i;
	char	*equal_ptr;
	char	*existing_var;

	equal_ptr = ft_strchr(input, '=');
	existing_var = find_var_exp(env, name_variable_index, &input);
	if (equal_ptr == NULL && existing_var != NULL)
		return (env);
	i = ft_strlen(input);
	if (equal_ptr != NULL && equal_ptr[1] == '\0')
		i += 2;
	j = 0;
	while (env[j] != NULL && env[j] != existing_var)
		j++;
	env = set_new_var(env, existing_var, i, j);
	if (env == NULL)
		return (NULL);
	ft_strlcpy(env[j], input, i + 1);
	return (env);
}
