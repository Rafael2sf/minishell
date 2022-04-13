/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:03:52 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/13 11:43:11 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static void	check_parameter(char **input);

int	ft_exit(char **input, int fd, int *stat, char ***env)
{
	(void)(env);
	close(fd);
	ft_putendl_fd("exit", 1);
	if (input[1] != NULL && input[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (input[1] == NULL)
		exit(*stat);
	check_parameter(input);
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
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(input[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(-1);
		}
	}
}
