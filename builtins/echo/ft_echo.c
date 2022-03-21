/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:53 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/21 15:37:27 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"

int	flag_status(char *input, int *i)
{
	if (input[0] == '-' && input[1] == 'n')
	{	
		*i = 2;
		if (ft_strncmp(input, "-n", 3) == 0)
			return (1);
		if (input[2] == ' ')
		{
			*i = 3;
			return (1);
		}
		else if (input[2] != '\0')
			*i = 0;
	}
	return (0);
}

int	ft_echo(char *input, int fd)
{
	char	*output;
	int		i;
	int		j;
	int		flag;
	
	i = 0;
	j = 0;
	output = malloc(sizeof(char) * (ft_strlen(input) + 2));
	if (!output)
		return (-1);
	flag = flag_status(input, &i);
	while (input[i] != '\0')
	{
		if (input[i] != '\'' && input[i] != '\"')
			output[j++] = input[i++];
		else
			i++;
	}
	if (!flag)
		output[j++] = '\n';
	output[j] = '\0';
	write(fd, output, j + 1);
	free(output);
	return (0);
}

int	main(void)
{
	char 	*input = "-na\n";

	ft_echo(input, 1);
	return (0);
}