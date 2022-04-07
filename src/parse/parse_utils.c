/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:12:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/06 11:21:24 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	pvars_init(t_pvars *v)
{
	(v->quote) = 0;
	(v->dquote) = 0;
	(v->start) = 0;
	(v->end) = 0;
}

void	ms_parse_quotes(char c, t_pvars *v)
{
	if (c == '\'')
	{
		if (v->dquote == 0)
		{
			if (v->quote == 0)
				(v->quote) += 1;
			else
				(v->quote) -= 1;
		}
	}
	else if (c == '\"')
	{
		if (v->quote == 0)
		{
			if (v->dquote == 0)
				(v->dquote) += 1;
			else
				(v->dquote) -= 1;
		}
	}
}

int	ms_parse_error(int code, char c, bool use_perror)
{
	if (use_perror)
		perror("minishell");
	else if (code != 0)
	{
		ft_putstr(STDERR_FILENO, "minishell: parse error near `");
		ft_putchar(STDERR_FILENO, c);
		ft_putstr(STDERR_FILENO, "\'\n");
	}
	return (code);
}
