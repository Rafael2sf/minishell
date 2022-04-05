/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:50:08 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 10:32:21 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

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

	if (!*input)
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

static int	change_pwd_vars(char *var_id, int fd, char ***env, char *buf)
{
	int		err_val;
	char	*pwd_change[3];

	err_val = 0;
	pwd_change[0] = "export";
	pwd_change[1] = ft_strjoin(var_id, buf);
	pwd_change[2] = NULL;
	if (!pwd_change[1])
		return (errno);
	err_val = ft_export(pwd_change, fd, env);
	if (err_val)
		return (err_val);
	free(pwd_change[1]);
	return (0);
}

static int	pwd_change(int fd, char ***env)
{
	int		err_val;
	char	buf[1024];

	if (getcwd(buf, 1024) == NULL)
	{
		perror("getcwd failed");
		return (errno);
	}
	err_val = change_pwd_vars("PWD=", fd, env, buf);
	if (err_val)
		return (err_val);
	return (0);
}

int	ft_cd(char **input, int fd, char ***env)
{
	char	buf[1024];
	int		err_val;

	close(fd);
	if (null_input_check(&input[1], *env) == 0)
		return (-1);
	else if (!input[1][0])
		return (0);
	if (getcwd(buf, 1024) == NULL)
	{
		perror("getcwd failed");
		return (errno);
	}
	if (chdir(input[1]) == -1)
	{
		error_message(input[1]);
		return (errno);
	}
	err_val = change_pwd_vars("OLDPWD=", fd, env, buf);
	if (err_val)
		return (err_val);
	return (pwd_change(fd, env));
}

// int	main(int ac, char **av, char **env)
// {
// 	char	**env_cpy;
// 	int		i =0;
// 	char	*test[3] = {"cd", "", NULL};
// 	(void) ac;
// 	(void) av;
//
// 	env_cpy = creat_copy(env);
// 	ft_cd(test, 1, &env_cpy);
// 	while (env_cpy[i])
// 	{
// 		printf("%s\n",env_cpy[i++]);
// 	}
// 	ptr_ptr_free((void **) env_cpy);
// 	return (0);
// }
