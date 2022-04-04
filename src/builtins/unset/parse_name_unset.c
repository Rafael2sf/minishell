/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:38:49 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:19 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../../../headers/builtins.h"

static int	check_first_c(char *input)
{
	if (ft_isdigit(input[0]) || input[0] == '\0')
	{
		ft_putstr_fd("unset: ", 2);
		ft_putchar_fd('`', 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\': ", 2);
		ft_putendl_fd("not a valid identifier", 2);
		return (0);
	}
	return (1);
}

int	parsing_input_name_unset(char **input)
{
	int		i;

	i = 0;
	if (check_first_c(*input) == 0)
		return (0);
	while ((*input)[i] != '\0')
	{
		if (!ft_isalnum((*input)[i]) && (*input)[i] != '_')
		{	
			ft_putstr_fd("unset: ", 2);
			ft_putchar_fd('`', 2);
			ft_putstr_fd(*input, 2);
			ft_putstr_fd("\': ", 2);
			ft_putendl_fd("not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (i);
}
