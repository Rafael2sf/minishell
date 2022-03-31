/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:53 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/30 15:05:18 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

int	ft_echo(char **input, int fd)
{
	int		i;
	int		flag;

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
	return (0);
}

/*int	main(void)
{
	char 	*input[4] = {"echo", "-n", "Right HERE!", NULL};

	ft_echo(input, 1);
	return (0);
}*/