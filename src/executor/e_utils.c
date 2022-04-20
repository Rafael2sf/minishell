/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:41:22 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 10:42:43 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_parameter(char **input);

int	tk_close_all(t_ast *tk, void *p)
{
	(void)(p);
	if (!tk)
		return (0);
	if (tk->type == E_CMD || tk->type == E_UNDEF)
	{
		if ((tk->p)[0] > 2)
			close((tk->p)[0]);
		if ((tk->p)[1] > 2)
			close((tk->p)[1]);
	}
	return (0);
}

int	ms_valid_exit(t_ast *tokens)
{
	char		**data;

	data = (char **)(tokens->data);
	return (tokens->type == E_CMD && data && ft_strncmp(data[0], "exit", 5) == 0
		&& (!data[1] || (data[1] && !data[2]) || check_parameter(data) == -1));
}

static int	check_parameter(char **input)
{
	int	i;

	i = 0;
	while (ft_is(input[1][i], " \t"))
		i++;
	if (ft_is(input[1][i], "-+"))
		i++;
	while (input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i++]) || i == 20)
			return (-1);
	}
	return (0);
}
