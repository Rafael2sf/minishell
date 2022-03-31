/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:18:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:55 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

int	ft_env(char **input, char **env, int fd)
{
	int		i;

	(void) input;
	i = 0;
	while (env[i] != NULL)
		ft_putendl_fd(env[i++], fd);
	return (1);
}

/*int	main(int ac, char **av, char **env)
{
	ft_env(env,1);
	return (0);
}*/
