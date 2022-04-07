/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 10:31:54 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
	Create a new_token token
*/
t_ast	*tk_new_token(t_type type, void *ref)
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
		(new_token->pid) = 0;
		(new_token->p)[0] = 0;
		(new_token->p)[1] = 0;
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
int	tk_is_rd(t_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}

/*
	Free node data
*/
void	tk_free(void *tk_ptr)
{
	t_ast	*tk;
	char	**arr;
	int		i;

	i = 0;
	tk = (t_ast *)(tk_ptr);
	if (tk->type == E_CMD)
	{
		arr = (char **)(tk->data);
		while (arr[i])
			free(arr[i++]);
		free(tk->data);
	}
	else if (tk_is_rd(tk->type))
		free(tk->data);
	free(tk);
}
