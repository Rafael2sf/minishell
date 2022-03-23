/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:20:31 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/23 18:01:00 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ast_add_cmd(t_tk **root, t_tk *new_token);

/*
	Add a token to the ast based on it's type
*/
int	ast_add(t_tk **root, t_tk *new_token)
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
			if (new_token->type == E_LSR || E_GRT)
				((*root)->left) = new_token;
			else
				((*root)->right) = new_token;
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
	Add a token on top of root
*/
int	ast_add_top(t_tk **root, t_tk *new_token)
{
	if (!root || !*root || !new_token)
		return (1);
	(new_token->left) = *root;
	((*root)->prev) = new_token;
	(*root) = new_token;
	return (0);
}

/*
	Add a token on the left of root
*/
int	ast_add_left(t_tk **root, t_tk *new_token)
{
	if (!root || !*root || !new_token)
		return (1);
	if ((*root)->left)
	{
		(new_token->left) = ((*root)->left);
		((*root)->left->prev) = new_token;
	}
	((*root)->left) = new_token;
	(new_token->prev) = (*root);
	return (0);
}

/* 
	Add a token on the right of root
*/
int	ast_add_right(t_tk **root, t_tk *new_token)
{
	if (!root || !*root || !new_token)
		return (1);
	if ((*root)->right)
	{
		(new_token->right) = ((*root)->right);
		((*root)->right->prev) = new_token;
	}
	((*root)->right) = new_token;
	(new_token->prev) = (*root);
	return (0);
}

/*
	Adding token of type E_CMD to a ast 
*/
static int	ast_add_cmd(t_tk **root, t_tk *new_token)
{
	if (((*root)->type) == E_PIPE && !((*root)->right))
	{
		((*root)->right) = new_token;
		(new_token->prev) = ((*root)->right);
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
