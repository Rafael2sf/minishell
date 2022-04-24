/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:03:52 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/24 21:14:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static void	check_parameter(char **input);

int	ft_exit(char **input, int fd, int *stat, char ***env)
{
	(void)(env);
	if (fd > 2)
		close(fd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (input[1] == NULL)
		exit(*stat);
	check_parameter(input);
	if (input[1] != NULL && input[2] != NULL)
	{
		ft_putendl_fd("baby-sh: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	(*stat) = ft_atoi(input[1]);
	free(input[1]);
	exit(*stat);
}

static void	check_parameter(char **input)
{
	int	i;

	i = 0;
	while (ft_is(input[1][i], " \t"))
		i++;
	if (ft_is(input[1][i], "-+"))
		i++;
	while (input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i++]) || i == 20)
		{
			ft_putstr_fd("baby-sh: exit: ", STDERR_FILENO);
			ft_putstr_fd(input[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			free(input[1]);
			exit(-1);
		}
	}
}
