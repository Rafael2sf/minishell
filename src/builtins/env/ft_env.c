/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:18:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:15:31 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

int	ft_env(char **input, int fd, int *stat, char ***env)
{
	int		i;

	(void)(stat);
	(void)(input);
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strchr((*env)[i], '=') != NULL)
			ft_putendl_fd((*env)[i], fd);
		i++;
	}
	close(fd);
	return (0);
}
