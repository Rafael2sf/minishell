/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/23 18:01:32 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

/*
	Create a new_token token
*/
t_tk	*tk_new_token(enum e_type type, char *data)
{
	t_tk	*new_token;

	new_token = malloc(sizeof(t_tk));
	if (new_token)
	{
		(new_token->type) = type;
		(new_token->data) = data;
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
void	ast_iter(t_tk *root, void (*f)(void *))
{
	if (!root)
		return ;
	ast_iter(root->left, f);
	ast_iter(root->right, f);
	f(root);
}

/*
	Returns true if type is a redirection
*/
int	tk_is_rd(enum e_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}
