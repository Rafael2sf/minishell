/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:43 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/30 12:19:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	**set_variables(char *input, char **env)
{
	int			name_variable_index;
	int			i;

	i = 0;
	name_variable_index = parsing_input_name_export(input);
	if (!name_variable_index)
		return (env);
	env = prep_output(input, env, name_variable_index);
	if (!env)
		return (NULL);
	return (env);
}

static void	print_export(char **env_cpy, int fd, char *ptr)
{
	int		i;
	int		j;

	i = 0;
	while (env_cpy[i] != NULL)
	{
		if (ft_strncmp(env_cpy[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd);
		j = 0;
		ptr = ft_strchr(env_cpy[i], '=');
		while (env_cpy[i][j] != '=' && env_cpy[i][j] != '\0')
			ft_putchar_fd(env_cpy[i][j++], fd);
		if (ptr != NULL)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(++ptr, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
}

static void	env_to_export(char **env, int fd)
{
	char	**env_cpy;
	int		total;
	char	*ptr;

	ptr = NULL;
	env_cpy = creat_copy(env);
	total = get_total(env_cpy);
	sort_env_cpy(env_cpy, total);
	print_export(env_cpy, fd, ptr);
	ptr_ptr_free((void **) env_cpy);
}

char	**ft_export(char **input, int fd, char **env)
{
	int	i;

	i = 1;
	if (!env)
	{
		ft_putendl_fd("error: env does not exist", 2);
		return (NULL);
	}
	while (input[i] != NULL && input[i][0] != '\0')
		env = set_variables(input[i++], env);
	if (input[1] == NULL)
		env_to_export(env, fd);
	return (env);
}

/*int	main(int ac, char **av, char **env)
{
	int		i;
	char	**env_cpy;
	char	*input[4];
	char	*input2[2];

	(void) ac;
	(void) av;
	input[0] = "export";
	input[1] = "TE1ST=12345 just+-!/? playing";
	input[2] = "TEST2=";
	input[3] = NULL;
	input2[0] = "export";
	input2[1] = NULL;
	i = 0;
	env_cpy = creat_copy(env);
	env_cpy = ft_export(input, 1, env_cpy);
	env_cpy = ft_export(input2, 1, env_cpy);
	printf("\n\n\n");
	// sleep(3);
	// input[0] = "unset";
	// input[1] = "TE1ST";
	// input[2] = "TEST2";
	// env_cpy = ft_unset(input, 1, env_cpy);
	// env_cpy = ft_export(input2, 1, env_cpy);
	ptr_ptr_free((void **) env_cpy);
	return (0);
}*/
