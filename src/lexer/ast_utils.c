/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/11 10:31:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "lexer.h"

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
		(new_token->pid) = -1;
		(new_token->p)[0] = -1;
		(new_token->p)[1] = -1;
		(new_token->func) = NULL;
		return (new_token);
	}
	return (NULL);
}

/*
	Returns true if type is a redirection
*/
int	tk_is_rd(t_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}

/*
	Free ast
*/
void	ast_free(t_ast **tk)
{
	char	**arr;
	int		i;

	if (!tk || !*tk)
		return ;
	i = 0;
	if ((*tk)->left)
		ast_free(&((*tk)->left));
	if ((*tk)->right)
		ast_free(&((*tk)->right));
	if (((*tk)->type) == E_CMD)
	{
		arr = (char **)((*tk)->data);
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	else if (tk_is_rd((*tk)->type))
		free((char *)((*tk)->data));
	free(*tk);
}
