/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:27 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/29 16:28:31 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

int	ft_pwd(char *input, int fd, char **env)
{
	int	i;
	char	*pwd;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
		{
			pwd = &env[i][5];
			break ;
		}
		i++;
	}
	write(fd, pwd, ft_strlen(pwd) + 1);
	return (0);
}
