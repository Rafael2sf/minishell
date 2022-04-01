/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:50:08 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/31 14:58:57 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "../export/ft_export.h"

static void	error_message(char *input)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

static int	null_input_check(char **input, char **env)
{
	int		i;

	if (!*input || !(*input)[0])
	{
		i = 0;
		while (env[i] != NULL)
		{
			if (ft_strncmp("HOME=", env[i], 5) == 0)
			{
				*input = &env[i][5];
				break ;
			}
			i++;
		}
		if (env[i] == NULL)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (0);
		}
	}
	return (1);
}

char	**ft_cd(char **input, int fd, char **env)		//fd?????
{
	char	buf[1024];
	char	*pwd_change;

	if (null_input_check(&input[1], env) == 0)
		return (env);
	getcwd(buf, 1024);
	if (chdir(input[1]) == -1)
	{
		error_message(input[1]);
		return (env);
	}
	pwd_change = ft_strjoin("OLDPWD=", buf);
	env = ft_export(pwd_change, fd, env);
	free(pwd_change);
	getcwd(buf, 1024);
	pwd_change = ft_strjoin("PWD=", buf);
	env = ft_export(pwd_change, fd, env);
	free(pwd_change);
	return (env);
}

int	main(int ac, char **av, char **env)
{
	char	**env_cpy;
	(void) ac;
	(void) av;

	env_cpy = creat_copy(env);
	ft_cd(NULL, 1, env_cpy);
	ptr_ptr_free((void **) env_cpy);
	return (0);
}
