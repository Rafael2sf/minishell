/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:27 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:18:17 by rafernan         ###   ########.fr       */
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
	if (getcwd(buf, 1024) == NULL)
	{
		perror("getcwd failed");
		return (errno);
	}
	ft_putendl_fd(buf, fd);
	close(fd);
	return (0);
}
