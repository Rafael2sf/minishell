/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/24 21:14:43 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static int	error_printing(char *input, char c_check)
{
	if (!ft_isalnum(c_check) && c_check != '_')
	{	
		ft_putstr_fd("baby-sh: export: `", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	parsing_input_name_export(char *input)
{
	int			i;

	i = 0;
	if (ft_isdigit(input[0]) || input[0] == '\0')
	{
		ft_putstr_fd("baby-sh: export: `", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putendl_fd("\':not a valid identifier", STDERR_FILENO);
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
