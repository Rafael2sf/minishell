/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:35:43 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 16:02:17 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ast_add_cmd(t_ast **root, t_ast *new_token);
static int	ast_add_rd(t_ast **root, t_ast *new_token);
static int	ast_add_rd_in(t_ast **root, t_ast *new_token);
static int	ast_add_rd_out(t_ast **root, t_ast *new_token);

/*
	Add a token to the ast based on it's type
*/
int	ast_add(t_ast **root, t_ast *new_token)
{
	if (!root || !new_token)
		return (1);
	if (!*root)
	{
		if (tk_is_rd(new_token->type))
		{
			(*root) = tk_new_token(E_UNDEF, NULL);
			if (!*root)
				return (-1);
			if (new_token->type == E_LSR || new_token->type == E_LLSR)
				((*root)->left) = new_token;
			else
				((*root)->right) = new_token;
			(new_token->prev) = (*root);
		}
		else
			(*root) = new_token;
		return (0);
	}
	if (new_token->type == E_CMD || new_token->type == E_UNDEF)
		return (ast_add_cmd(root, new_token));
	else if (new_token->type == E_PIPE)
		return (ast_add_top(root, new_token));
	return (ast_add_rd(root, new_token));
}

/*
	Adding token of type E_CMD to a ast 
*/
static int	ast_add_cmd(t_ast **root, t_ast *new_token)
{
	if (((*root)->type) == E_PIPE && !((*root)->right))
	{
		((*root)->right) = new_token;
		(new_token->prev) = (*root);
		return (0);
	}
	else if (((*root)->type) == E_UNDEF)
	{
		((*root)->type) = E_CMD;
		((*root)->data) = (new_token->data);
		free(new_token);
		return (0);
	}
	else if ((*root)->right)
		return (ast_add_cmd(&(*root)->right, new_token));
	return (1);
}

/*
	Adding token of type redireciton to a ast 
*/
static int	ast_add_rd(t_ast **root, t_ast *new_token)
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
static int	ast_add_rd_in(t_ast **root, t_ast *new_token)
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
static int	ast_add_rd_out(t_ast **root, t_ast *new_token)
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
