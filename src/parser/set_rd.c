/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:33:47 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/22 10:28:51 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ms_reset_tk(int code, t_ast *tk, int *stat);
static int	tk_set_rd_actions(t_ast *tk, t_mshell *shell);

int	tk_set_rd(t_ast *tk, void *p)
{
	t_mshell	*shell;

	shell = (t_mshell *)(p);
	if (!tk)
		return (0);
	if (tk->type == E_CMD || tk->type == E_UNDEF)
		return (tk_set_rd_actions(tk, shell));
	return (0);
}

static int	tk_set_rd_actions(t_ast *tk, t_mshell *shell)
{
	(tk->p)[0] = ms_parse_input(tk, shell);
	if ((tk->p[0]) == -1)
	{
		if (tk->prev && tk->prev->left == tk)
			close((tk->prev->p)[1]);
		else if (tk->prev && tk->prev->prev)
			close((tk->prev->prev->p)[1]);
		return (ms_reset_tk(1, tk, &(shell->stat)));
	}
	(tk->p)[1] = ms_parse_output(tk);
	if (tk->p[1] == -1)
		return (ms_reset_tk(1, tk, &(shell->stat)));
	if (tk->type == E_UNDEF)
	{
		if (tk_is_last(tk))
			(shell->stat) = 0;
		return (0);
	}
	(tk->func) = ms_find_builtin(((char **)(tk->data))[0]);
	if (tk->func)
		return (0);
	if (!ms_parse_cmd(&((char **)tk->data)[0], tk, shell))
		return (ms_reset_tk(1, tk, NULL));
	return (0);
}

static int	ms_reset_tk(int code, t_ast *tk, int *stat)
{
	if (stat && tk_is_last(tk))
		(*stat) = 1;
	ptr_ptr_free((char **)tk->data);
	(tk->data) = NULL;
	(tk->type) = E_UNDEF;
	return (code);
}
