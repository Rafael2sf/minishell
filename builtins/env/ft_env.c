/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:18:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/22 12:08:26 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

void	full_env_list(char *output, char **env, int *total)
{
	int		i;
	int		j;

	i = 0;
	*total = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			output[(*total)++] = env[i][j++];
		}
		output[(*total)++] = '\n';
		i++;
	}
	output[(*total)] = '\0';
}

int	ft_env(char *input, int fd, char **env)
{
	int	i;
	int	j;
	int total;
	char	*output;

	if (!env)
		return (-1);
	i = 0;
	total = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
			j++;
		total += j;
		i++;
	}
	output = malloc(sizeof(char) * (total + i + 1));
	if (!output)
		return (-1);
	full_env_list(output, env, &total);
	write(fd, output, total + 1);
	free(output);
	return (1);
}

/*int	main(int ac, char **av, char **env)
{
	int	i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i++]);
	}
	ft_env(NULL, 1, env);
	return (0);
}*/


