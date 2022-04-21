/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:27 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 10:40:07 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

int	ft_pwd(char **input, int fd, int *stat, char ***env)
{
	char	buf[1024];

	(void)(env);
	(void)(input);
	(void)(stat);
	if (fd < 2)
		return (1);
	if (getcwd(buf, 1024) == NULL)
	{
		werror("pwd");
		return (errno);
	}
	ft_putendl_fd(buf, fd);
	close(fd);
	return (0);
}
