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
#include "../../../headers/builtins.h"

int	ft_env(char **input, int fd, char **env)
{
	int		i;

	(void) input;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			ft_putendl_fd(env[i], fd);
		i++;
	}
	close(fd);
	return (0);
}

/*int	main(int ac, char **av, char **env)
{
	ft_env(env,1);
	return (0);
}*/
