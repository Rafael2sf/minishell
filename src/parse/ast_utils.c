/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/22 11:27:46 by rafernan         ###   ########.fr       */
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
void	ast_iter(t_tk *root, void (*f)(t_tk *, int), int depth)
{
	if (!root)
		return ;
	ast_iter(root->left, f, depth + 1);
	f(root, depth);
	ast_iter(root->right, f, depth + 1);
}

/*
	Returns true if type is a redirection
*/
int	tk_is_rd(enum e_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}

/* ----- TEST  -------

void	tk_print(t_tk *tk, int depth)
{
	while (depth-- > 0)
		printf("\t");
	printf("(%d,%s)\n", (int)(tk->type), (tk->data));
}

int	main(void)
{
	char	*s[] = {"< in", "wc", "echo", "cat", "> out"};
	t_tk	*tree;

	tree = NULL;
	ast_add(&tree, tk_new_token(E_LSR, s[0]));
	ast_add(&tree, tk_new_token(E_GRT, s[4]));
	ast_add(&tree, tk_new_token(E_CMD, s[1]));
	ast_add(&tree, tk_new_token(E_PIPE, NULL));
	ast_add(&tree, tk_new_token(E_LSR, s[0]));
	ast_add(&tree, tk_new_token(E_CMD, s[2]));
	ast_add(&tree, tk_new_token(E_PIPE, NULL));
	ast_add(&tree, tk_new_token(E_CMD, s[3]));
	
	ast_iter(tree, tk_print, 0);
	return (0);
}
 */
