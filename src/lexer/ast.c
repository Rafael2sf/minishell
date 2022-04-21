/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:20:31 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 18:02:08 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	Add a token on top of root
*/
int	ast_add_top(t_ast **root, t_ast *new_token)
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
int	ast_add_left(t_ast **root, t_ast *new_token)
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
int	ast_add_right(t_ast **root, t_ast *new_token)
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
