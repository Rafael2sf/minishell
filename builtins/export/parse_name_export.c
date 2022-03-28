/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:52:24 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

int	error_printing(char *split_input, char c_check, int *error_count)
{
	int	j;

	j = 0;
	if (!ft_isalnum(c_check) && c_check != '_' && *error_count == 0)
	{	
		ft_putstr_fd("export: not valid in this context: ", 2);
		while (split_input[j] != '\0' && split_input[j] != '=')
			ft_putchar_fd(split_input[j++], 2);
		ft_putchar_fd('\n', 2);
		(*error_count)++;
		return (0);
	}
	return (1);
}

int	parsing_input_name_export(char *split_input, int *error_count)
{
	int			i;
	int			j;
	char		*name;

	i = 0;
	j = 0;
	if (ft_isdigit(split_input[0]) && *error_count == 0)
	{
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putendl_fd(split_input, 2);
		(*error_count)++;
		return (0);
	}
	while (split_input[i] != '\0' && split_input[i] != '=')
	{
		if (!error_printing(split_input, split_input[i], error_count))
			return (0);
		i++;
	}
	return (i);
}
