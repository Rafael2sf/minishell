/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:43 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/24 21:14:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static int	set_variables(char *input, char ***env);
static void	print_export(char **env_cpy, int fd, char *ptr);
static void	env_to_export(char **env, int fd);

int	ft_export(char **input, int fd, int *stat, char ***env)
{
	int	i;
	int	err_val;

	if (fd < 2)
		return (1);
	(void)(stat);
	i = 1;
	if (!*env)
	{
		ft_putendl_fd("baby-sh: export: ENV is empty", STDERR_FILENO);
		return (1);
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

static int	set_variables(char *input, char ***env)
{
	int			name_variable_index;

	name_variable_index = parsing_input_name_export(input);
	if (!name_variable_index)
		return (1);
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
	env_cpy = ptr_ptr_dup(env);
	total = get_total(env_cpy);
	sort_env_cpy(env_cpy, total);
	print_export(env_cpy, fd, ptr);
	ptr_ptr_free(env_cpy);
}
