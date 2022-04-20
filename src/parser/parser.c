/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:53:18 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 19:58:33 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static int	tk_expand(t_ast *tk, void *shell_ptr);
static int	tk_open_pipes(t_ast *tk, void *p);
static int	tk_hdoc(t_ast *tk, void *p);

int	ms_parser(t_mshell *shell)
{
	if (DEBUG)
	{
		printf("\t <-- LEXER --> \n");
		ast_print(shell->tokens, 0, 0);
	}
	if (ast_iter_in(shell->tokens, tk_expand, 0, (void *)(shell)) == -1)
		return (ms_parse_error(-1, shell));
	if (ast_iter_pre(shell->tokens, tk_open_pipes, 0, (void *)(shell)) == -1)
		return (ms_parse_error(-1, shell));
	if (ast_iter_in(shell->tokens, tk_hdoc, 0, (void *)(shell)) == -1)
		return (ms_parse_error(0, shell));
	(shell->paths) = ms_parse_paths(shell->env);
	if (ast_iter_in(shell->tokens, tk_set_rd, 0, (void *)(shell)) == -1)
		return (ms_parse_error(-1, shell));
	ptr_ptr_free((void **)(shell->paths));
	(shell->paths) = NULL;
	return (0);
}

static int	e_cmd_tk_expand(t_mshell *shell, t_ast *tk)
{
	int			i;
	char		**ref;
	char		*tmp;

	i = -1;
	ref = (char **)(tk->data);
	while (ref && ref[++i])
	{
		tmp = ms_expand(ref[i], shell, 0);
		if (!tmp)
			return (-1);
		if (tmp != ref[i])
		{
			free(ref[i]);
			ref[i] = tmp;
		}
	}
	return (0);
}

static int	tk_expand(t_ast *tk, void *p)
{
	char		*tmp;
	t_mshell	*shell;

	shell = (t_mshell *)p;
	if (!tk)
		return (0);
	if (tk->type == E_CMD)
		return (e_cmd_tk_expand(shell, tk) == -1);
	else if (tk->type == E_LSR || tk->type == E_LLSR
		|| tk->type == E_GRT || tk->type == E_GGRT)
	{
		tmp = ms_expand((char *)tk->data, shell, 0);
		if (tmp && ((char *)tk->data) != tmp)
		{
			free((char *)tk->data);
			(tk->data) = tmp;
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
			return (-1);
		if (tk->left->type == E_CMD || tk->left->type == E_UNDEF)
			(tk->left->p)[1] = (tk->p)[1];
		else
			(tk->left->right->p)[1] = (tk->p)[1];
		(tk->right->p[0]) = (tk->p)[0];
	}
	return (0);
}

static int	tk_hdoc(t_ast *tk, void *p)
{
	t_mshell	*shell;
	int			fd;

	shell = (t_mshell *)(p);
	if (shell->sig_call == true)
		return (-1);
	if (!tk)
		return (0);
	if (tk->type == E_LLSR)
	{
		fd = ms_heredoc((char *)tk->data, shell);
		if (shell->sig_call == true)
			return (-1);
		if (fd == -1)
			werror(NULL);
		if (tk->prev->type == E_CMD || tk->prev->type == E_UNDEF)
		{
			if ((tk->prev->p)[0] > 2)
				close((tk->prev->p)[0]);
			(tk->prev->p)[0] = fd;
		}
		else if (fd > 2)
			close(fd);
	}
	return (0);
}
