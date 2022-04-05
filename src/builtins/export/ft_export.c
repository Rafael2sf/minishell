/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:43 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:34:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

static int	set_variables(char *input, char ***env)
{
	int			name_variable_index;
	int			i;

	i = 0;
	name_variable_index = parsing_input_name_export(input);
	if (!name_variable_index)
		return (-1);
	*env = prep_output(input, *env, name_variable_index);
	if (!*env)
		return (errno);
	return (0);
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

int	ft_export(char **input, int fd, char ***env)
{
	int	i;
	int	err_val;

	i = 1;
	if (!*env)
	{
		ft_putendl_fd("error: env does not exist", 2);
		return (-1);
	}
	while (input[i] != NULL)
	{
		err_val = set_variables(input[i++], env);
		if (err_val)
			return (err_val);
	}
	if (input[1] == NULL)
		env_to_export(*env, fd);
	close(fd);
	return (0);
}

/*
int	main(int ac, char **av, char **env)
{
	int		i;
	char	**env_cpy;
	char	*input[4];
	char	*input2[2];

	(void) ac;
	(void) av;
	input[0] = "export";
	input[1] = "TEST= 14";
	input[2] = "TEST2";
	input[3] = NULL;
	input2[0] = "export";
	input2[1] = NULL;
	i = 0;
	env_cpy = creat_copy(env);
	ft_export(input, 1, &env_cpy);
	ft_export(input2, 1, &env_cpy);
	printf("\n\n\n");
	sleep(3);
	input[0] = "unset";
	env_cpy = export_at_start_process(env_cpy);
	ft_export(input2, 1, &env_cpy);
	ptr_ptr_free((void **) env_cpy);
	return (0);
}
*/