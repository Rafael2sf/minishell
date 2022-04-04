/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:32 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

static int	error_printing(char *input, char c_check)
{
	int	j;

	j = 0;
	if (!ft_isalnum(c_check) && c_check != '_')
	{	
		ft_putstr_fd("export: ", 2);
		ft_putchar_fd('`', 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\': ", 2);
		ft_putendl_fd("not a valid identifier", 2);
		return (0);
	}
	return (1);
}

int	parsing_input_name_export(char *input)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (ft_isdigit(input[0]) || input[0] == '\0')
	{
		ft_putstr_fd("export: ", 2);
		ft_putchar_fd('`', 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\': ", 2);
		ft_putendl_fd("not a valid identifier", 2);
		return (0);
	}
	while (input[i] != '\0' && input[i] != '=')
	{
		if (!error_printing(input, input[i]))
			return (0);
		i++;
	}
	return (i);
}
