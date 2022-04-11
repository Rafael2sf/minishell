/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:53:18 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/11 12:08:46 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static int	tk_expand(t_ast *tk, void *p);
static int	ms_reset_tk(int code, t_ast *tk);
static int	tk_open_pipes(t_ast *tk, void *p);
static int	tk_set_rd(t_ast *tk, void *p);

int	ms_parser(t_ast	*root)
{
	char	**paths;
	int		ret;

	ret = 0;
	if (DEBUG)
	{
		printf("\t <-- LEXER -> \n");
		ast_print(root, 0, 0);
	}
	if (ast_iter_in(root, tk_expand, 0, NULL) == -1)
		return (ms_parse_error(-1));
	if (ast_iter_pre(root, tk_open_pipes, 0, NULL) == -1)
		return (ms_parse_error(-1)); // call tk_close_all
	paths = ms_parse_paths();
	ret = ast_iter_in(root, tk_set_rd, 0, (void *)(paths));
	if (paths)
		ptr_ptr_free((void **)(paths));
	if (ret == -1) // call tk_close_all
		return (ms_parse_error(-1));
	return (0);
}

static int	tk_expand(t_ast *tk, void *p)
{
	char	**ref;
	char	*tmp;
	int		i;

	(void)(p);
	if (!tk)
		return (0);
	if (tk->type == E_CMD)
	{
		i = -1;
		ref = (char **)(tk->data);
		while (ref[++i])
		{
			tmp = ms_expand(ref[i]);
			if (!tmp)
				return (-1);
			if (tmp != ref[i])
			{
				free(ref[i]);
				ref[i] = tmp;
			}
		}
	}
	return (0);
}

static int	tk_open_pipes(t_ast *tk, void *p)
{
	(void)(p);
	if (!tk)
		return (0);
	if (tk->type == E_PIPE)
	{
		if (pipe(tk->p) == -1)
		{
			perror("minishell: ");
			return (-1);
		}
	}
	return (0);
}

static int	tk_set_rd(t_ast *tk, void *p)
{
	if (!tk)
		return (0);
	if (tk->type == E_CMD || tk->type == E_UNDEF)
	{
		(tk->p)[0] = ms_parse_input(tk);
		ast_free(&tk->left);
		(tk->left) = NULL;
		(tk->p)[1] = ms_parse_output(tk);
		if (tk->p[1] == -1 || (tk->p)[0] == -1)
			return (ms_reset_tk(1, tk));
		ast_free(&tk->right);
		(tk->right) = NULL;
		if (tk->type == E_UNDEF)
			return (0);
		(tk->func) = ms_find_builtin(((char **)tk->data)[0]);
		if (tk->func)
			return (0);
		if (!ms_parse_cmd(&((char **)tk->data)[0], (char **)(p)))
			return (ms_reset_tk(1, tk));
	}
	return (0);
}

static int	ms_reset_tk(int code, t_ast *tk)
{
	ptr_ptr_free((void **)tk->data);
	(tk->data) = NULL;
	(tk->type) = E_UNDEF;
	return (code);
}
