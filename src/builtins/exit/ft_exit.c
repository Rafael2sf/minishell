/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:03:52 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 18:29:45 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

int	ft_exit(char **input, int fd, char **env, int *stat)
{
	int	i;

	i = 0;
	close(fd);
	ft_putendl_fd("exit", 1);
	if (input[1] != NULL && input[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	ptr_ptr_free((void **)env);
	if (input[1] == NULL)
		exit(*stat);
	while (ft_is(input[1][i], " \t"))
		i++;
	if (ft_is(input[1][i], "-+"))
		i++;
	while (input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i++]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(input[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(-1);
		}
	}
	*stat = ft_atoi(input[1]);
	exit(*stat);
}

/*int	main(int ac, char **av, char **env)
{
	char	**env_cpy;
	int		i;

	(void) ac;
	(void) av;
	i = 0;
	env_cpy = creat_copy(env);
	ft_exit(av, 1, env_cpy);
	ptr_ptr_free((void **)env_cpy);
	return (0);
}*/
