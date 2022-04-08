/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:03:00 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 12:17:44 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ms_parse_last(char *line, t_pvars *v, t_ast **root);

int	ms_parse(t_ast **root, char *line)
{
	t_pvars	v;

	pvars_init(&v);
	while (*line && ft_is(*line, " \t"))
		line++;
	if (*line == '|')
		return (ms_parse_error(-1, '|', 0));
	if (!line)
		return (1);
	while (1)
	{
		if (line[v.end] == '\0')
			return (ms_parse_last(line, &v, root));
		ms_parse_quotes(line[v.end], &v);
		if (v.quote == 0 && v.dquote == 0 && ft_is(line[v.end], ">|<"))
		{
			if (ms_parse_token(root, line, &v) != 0)
				return (-1);
			(v.start) = (v.end);
		}
		else
			(v.end) += 1;
	}
	return (0);
}

static int	ms_parse_last(char *line, t_pvars *v, t_ast **root)
{
	if (v->quote != 0 || v->dquote != 0)
	{
		if (v->quote >= v->dquote)
			return (ms_parse_error(-1, '\'', 0));
		else
			return (ms_parse_error(-1, '\"', 0));
	}
	while (--v->end >= v->start && ft_is(line[v->end], " \t"))
		;
	if (v->end - v->start >= 0)
		ms_create_token(root, E_CMD, &line[v->start],
			v->end - v->start + 1);
	return (0);
}
