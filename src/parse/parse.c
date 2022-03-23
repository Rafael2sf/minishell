/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:03:00 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/23 18:00:05 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ms_parse_token(t_tk **root, const char *line, t_pvars *vars);
static int	ms_parse_pipe(t_tk **root, const char *line, t_pvars *vars);
static int	ms_parse_rd(t_tk **root, const char *line, t_pvars *vars);
static void	ms_parse_quotes(char c, t_pvars *v);
static int	ms_parse_last(const char *line, t_pvars *v, t_tk **root);

int	ms_parse(t_tk **root, const char *line)
{
	t_pvars	v;

	pvars_init(&v);
	while (*line && *line == ' ')
		line++;
	if (*line == '|')
		return (ms_parse_error(-1, '|'));
	while (1)
	{
		if (line[v.end] == '\0')
			return (ms_parse_last(line, &v, root));
		ms_parse_quotes(line[v.end], &v);
		if (v.quote == 0 && v.dquote == 0 && ft_is(line[v.end] , ">|<"))
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

static int	ms_parse_token(t_tk **root, const char *line, t_pvars *v)
{
	int	tmp;
	int	ret;
	
	tmp = (v->end) - 1;
	// Remove spaces before
	while (tmp >= 0 && line[tmp] == ' ')
		tmp--;
	// get previous word
	// if (tmp - v->start >= 0)
	// 	write(1, &line[v->start], tmp - v->start + 1); // Set word if exists
	if (tmp - v->start >= 0)
		ms_create_token(root, E_CMD, &line[v->start], tmp - v->start + 1);
	// Handle case
	if (line[v->end] == '|')
		ret = ms_parse_pipe(root, line, v);
	else
		ret = ms_parse_rd(root, line, v);

	// Skip spaces
	while (line[v->end] && line[v->end] == ' ')
		(v->end)++;
	return  (ret);
}

static int	ms_parse_pipe(t_tk **root, const char *line, t_pvars *v)
{
	int	tmp;

	tmp = (v->end) + 1;
	while (line[tmp] == ' ')
		tmp++;
	if (line[tmp] == '|' || line[tmp] == '\0')
		return (ms_parse_error(-1, '|'));
	ms_create_token(root, E_PIPE, NULL, 0);
	//write(1, &line[v->end], 1);
	(v->end) += 1;
	return (0);
}

static int	ms_parse_rd(t_tk **root, const char *line, t_pvars *v)
{
	enum e_type	type;
	int			err_loc;

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
		return (ms_parse_error(-1, line[err_loc]));
	(v->start) = (v->end);
	
	while (line[v->end] && line[v->end] != ' ')
		(v->end) += 1;
	//write(1, &line[v->start], v->end - v->start); // Create word
	ms_create_token(root, type, &line[v->start], v->end - v->start);
	return (0);
}

static void	ms_parse_quotes(char c, t_pvars *v)
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

static int	ms_parse_last(const char *line, t_pvars *v, t_tk **root)
{
	if (line[v->end] == '\0')
	{
		if (v->quote != 0 || v->dquote != 0)
		{
			if (v->quote >= v->dquote)
				return (ms_parse_error(-1, '\''));
			else
				return (ms_parse_error(-1, '\"'));
		}
		while (--v->end >= v->start && line[v->end] == ' ')
			;
		// if (v->end - v->start >= 0)
		// 	write(1, &line[v->start], v->end - v->start + 1);
		if (v->end - v->start >= 0)
			ms_create_token(root, E_CMD, &line[v->start], v->end - v->start + 1);
	}
	return (0);
}

/* ---------- TEST ----------- */

void	tk_print(void *tk_ptr)
{
	t_tk	*tk;

	tk = (t_tk *)(tk_ptr);
	printf("(%d,%s)\n", (int)(tk->type), (tk->data));
}

void	tk_free(void *tk_ptr)
{
	t_tk	*tk;

	tk = (t_tk *)(tk_ptr);
	if (tk->data)
		free(tk->data);
	free(tk);	
}

int	main(int argc, char **argv)
{
	t_tk	*ast;
	
	if (argc == 2)
	{
		ast = NULL;
		if (ms_parse(&ast, argv[1]) == 0)
			ast_iter(ast, tk_print);
		ast_iter(ast, tk_free);
	}
}
