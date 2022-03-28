/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/25 11:12:15 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

/*
	Create a new_token token
*/
t_ast	*tk_new_token(enum e_type type, void *ref)
{
	t_ast	*new_token;

	new_token = malloc(sizeof(t_ast));
	if (new_token)
	{
		(new_token->type) = type;
		(new_token->data) = ref;
		(new_token->prev) = NULL;
		(new_token->left) = NULL;
		(new_token->right) = NULL;
		return (new_token);
	}
	return (NULL);
}

/*
	Recursively iterate the tree from left to right 
*/
void	ast_iter(t_ast *root, void (*f)(void *))
{
	if (!root)
		return ;
	ast_iter(root->left, f);
	f(root);
	ast_iter(root->right, f);
}

/*
	Returns true if type is a redirection
*/
int	tk_is_rd(enum e_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}
