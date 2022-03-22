/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_rd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:35:43 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/22 11:19:06 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ast_add_rd_in(t_tk **root, t_tk *new_token);
static int	ast_add_rd_out(t_tk **root, t_tk *new_token);

/*
	Adding token of type redireciton to a ast 
*/
int	ast_add_rd(t_tk **root, t_tk *new_token)
{
	if (!root || !*root || !new_token)
		return (1);
	if (new_token->type == E_LSR || new_token->type == E_LLSR)
		return (ast_add_rd_in(root, new_token));
	else
		return (ast_add_rd_out(root, new_token));
}

/*
	Handle adding token of type << or < to a ast 
*/
static int	ast_add_rd_in(t_tk **root, t_tk *new_token)
{
	if (((*root)->type) == E_CMD || ((*root)->type) == E_UNDEF)
		return (ast_add_left(root, new_token));
	else if (((*root)->type) == E_PIPE)
	{
		if (!((*root)->right))
		{
			((*root)->right) = tk_new_token(E_UNDEF, NULL);
			if (!(*root)->right)
				return (-1);
		}
		return (ast_add_left(&((*root)->right), new_token));
	}
	return (1);
}

/*
	Handle adding token of type >> or > to a ast 
*/
static int	ast_add_rd_out(t_tk **root, t_tk *new_token)
{
	if (((*root)->type) == E_CMD || ((*root)->type) == E_UNDEF)
		return (ast_add_right(root, new_token));
	else if (((*root)->type) == E_PIPE)
	{
		if (!((*root)->right))
		{
			((*root)->right) = tk_new_token(E_UNDEF, NULL);
			if (!(*root)->right)
				return (-1);
		}
		return (ast_add_right(&((*root)->right), new_token));
	}
	return (1);
}
