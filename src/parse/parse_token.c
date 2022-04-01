/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:41:02 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/31 14:22:37 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ms_parse_pipe(t_ast **root, char *line, t_pvars *v);
static int	ms_parse_rd(t_ast **root, char *line, t_pvars *v);
static int	ms_get_rd_word(t_pvars *v, char *line);

int	ms_parse_token(t_ast **root, char *line, t_pvars *v)
{
	int	tmp;
	int	ret;

	ret = 0;
	tmp = (v->end) - 1;
	while (tmp >= 0 && line[tmp] == ' ')
		tmp--;
	if (tmp - v->start >= 0)
		ret = ms_create_token(root, E_CMD, &line[v->start], tmp - v->start + 1);
	if (ret == -1)
		return (-1);
	if (line[v->end] == '|')
		ret += ms_parse_pipe(root, line, v);
	else
		ret += ms_parse_rd(root, line, v);
	while (line[v->end] && line[v->end] == ' ')
		(v->end)++;
	return (ret);
}

static int	ms_parse_pipe(t_ast **root, char *line, t_pvars *v)
{
	int	tmp;

	tmp = (v->end) + 1;
	while (line[tmp] == ' ')
		tmp++;
	if (line[tmp] == '|' || line[tmp] == '\0')
		return (ms_parse_error(-1, '|', 0));
	(v->end) += 1;
	return (ms_create_token(root, E_PIPE, NULL, 0));
}

static int	ms_parse_rd(t_ast **root, char *line, t_pvars *v)
{
	t_type	type;
	int		err_loc;

	if (line[v->end] == '<')
		type = E_LSR;
	else
		type = E_GRT;
	err_loc = (v->end);
	(v->end) += 1;
	if (ft_is(line[v->end], "<>"))
	{
		if (line[v->end] == '<')
			type = E_LLSR;
		else
			type = E_GGRT;
			(v->end) += 1;
	}
	while (line[v->end] && line[v->end] == ' ')
		(v->end)++;
	if (ft_is(line[v->end], "<|>") || line[v->end] == '\0')
		return (ms_parse_error(-1, line[err_loc], 0));
	if (ms_get_rd_word(v, line) != 0)
		return (ms_parse_error(-1, line[err_loc], 0));
	return (ms_create_token(root, type, &line[v->start], v->end - v->start));
}

static int	ms_get_rd_word(t_pvars *v, char *line)
{
	(v->start) = (v->end);
	while (1)
	{
		if (v->quote == 0 && v->dquote == 0
			&& (ft_is(line[v->end], " <|>") || !line[v->end]))
			break ;
		if (!line[v->end])
			return (-1);
		ms_parse_quotes(line[v->end], v);
		(v->end) += 1;
	}
	return (0);
}
