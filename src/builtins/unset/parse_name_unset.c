/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:38:49 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 17:09:21 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

static int	check_first_c(char *input)
{
	if (ft_isdigit(input[0]) || input[0] == '\0')
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
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
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(*input, STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (i);
}
