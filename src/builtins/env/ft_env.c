/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:18:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:51 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

int	ft_env(char **input, char **env, int fd)
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
	return (1);
}

/*int	main(int ac, char **av, char **env)
{
	ft_env(env,1);
	return (0);
}*/
