/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:43 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:58:34 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

char	**real_set_variables(char **split_input, int *error_count, char **env)
{
	int			name_variable_index;
	int			i;

	i = 0;
	while (split_input[i] != NULL)
	{
		name_variable_index = parsing_input_name_export(split_input[i],
				error_count);
		if (!name_variable_index)
		{
			i++;
			continue ;
		}
		env = prep_output(split_input[i++], env, name_variable_index);
		if (!env)
			return (NULL);
	}
	*error_count = 0;
	return (env);
}

static char	**set_variables(char *input, char **env)
{
	char		**split_input;
	static int	error_count = 0;

	split_input = altered_split(input, ' ');
	if (!split_input)
	{
		perror("Error splitting input");
		return (NULL);
	}
	env = real_set_variables(split_input, &error_count, env);
	if (!env)
		return (NULL);
	ptr_ptr_free((void **) split_input);
	return (env);
}

void	env_to_export(char **env, int fd)
{
	char	**env_cpy;
	int		i;
	int		total;

	env_cpy = creat_copy(env);
	total = get_total(env_cpy);
	sort_env_cpy(env_cpy, total);
	i = 0;
	while (env_cpy[i] != NULL)
	{
		if (ft_strncmp(env_cpy[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		ft_putstr_fd(env_cpy[i++], fd);
		ft_putchar_fd('\n', fd);
	}
	ptr_ptr_free((void **) env_cpy);
}

char	**ft_export(char *input, int fd, char **env)
{
	if (!env)
	{
		ft_putendl_fd("error: env does not exist", 2);
		return (NULL);
	}
	if (input != NULL && input[0] != '\0')
		env = set_variables(input, env);
	else
		env_to_export(env, fd);
	return (env);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	env_cpy = creat_copy(env);
	//env_cpy = ft_export("TEST2", 1, env_cpy);
	env_cpy = ft_export("TEST=\"12345 just playing\" TES!T TEST2=", 1, env_cpy);
	env_cpy = ft_export(NULL, 1, env_cpy);
	printf("\n\n\n");
	sleep(3);
	env_cpy = ft_unset("1TESTLA= TEST TESTER= TEST2", 1, env_cpy);
	env_cpy = ft_export(NULL, 1, env_cpy);
	ptr_ptr_free((void **) env_cpy);
	return (0);
}
