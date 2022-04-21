/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:53 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 17:13:50 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

int	ft_echo(char **input, int fd, int *stat, char ***envp)
{
	int		i;
	int		flag;

	(void)(stat);
	(void)(envp);
	if (fd < 2)
		return (1);
	i = 1;
	flag = 0;
	if (input[1] != NULL && ft_strncmp("-n", input[1], 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (input[i] != NULL)
	{
		ft_putstr_fd(input[i++], fd);
		if (input[i] != NULL)
			ft_putchar_fd(' ', fd);
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	close(fd);
	return (0);
}
