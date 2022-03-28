/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:03:00 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/28 10:17:14 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ms_parse_last(const char *line, t_pvars *v, t_ast **root);

int	ms_parse(t_ast **root, const char *line)
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

static int	ms_parse_last(const char *line, t_pvars *v, t_ast **root)
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
		if (v->end - v->start >= 0)
			ms_create_token(root, E_CMD, &line[v->start],
				v->end - v->start + 1);
	}
	return (0);
}

/**/

void	tk_print(void *tk_ptr)
{
	t_ast	*tk;
	char	**ref;
	int		i;

	i = 0;
	tk = (t_ast *)(tk_ptr);
	if (tk->type == E_CMD)
	{
		printf("(");
		ref = (char **)(tk->data);
		while (ref[i])
			printf(".%s.", ref[i++]);
	}
	else if (tk->type == E_PIPE)
		printf("(|");
	else if (tk->type == E_LSR)
		printf("(< ");
	else if (tk->type == E_LLSR)
		printf("(<< ");
	else if (tk->type == E_GRT)
		printf("(> ");
	else if (tk->type == E_GGRT)
		printf("(>> ");
	if (tk_is_rd(tk->type))
		printf(" %s", (char *)(tk->data));
	printf(")");
}

void	tk_free(void *tk_ptr)
{
	t_ast	*tk;

	tk = (t_ast *)(tk_ptr);
	if (tk->data)
		free(tk->data);
	free(tk);
}

int	main(int argc, char **argv)
{
	t_ast	*ast;

	if (argc == 2)
	{
		ast = NULL;
		ms_parse(&ast, argv[1]);
		ast_iter(ast, tk_print);
		ast_iter(ast, tk_free);
	}
}
