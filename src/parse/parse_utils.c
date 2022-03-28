/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:12:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/28 10:16:13 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

int	ft_is(char c, char const *set)
{
	char	*tmp;

	tmp = (char *)set;
	while (tmp && *tmp)
	{
		if (c == *tmp)
			return (1);
		tmp++;
	}
	return (0);
}

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

int	ms_parse_error(int code, char c)
{
	if (code != 0)
		printf("minishell: parse error near `%c\'\n", c); // Not writing to stderr
	return (code);
}

/*
int	ft_is(char c, char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str++ == c)
			return (1);
	}
	if (*str == c)
		return (1);
	return (0);
}
*/
