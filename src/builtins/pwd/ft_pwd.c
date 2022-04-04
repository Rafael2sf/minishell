/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:27 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:29 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

int	ft_pwd(char **input, int fd, char **env)
{
	char	buf[1024];

	(void) env;
	(void) input;
	if (getcwd(buf, 1024) == NULL)
	{
		perror("getcwd failed");
		return (errno);
	}
	ft_putendl_fd(buf, fd);
	return (0);
}
