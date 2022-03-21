/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:55:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/21 18:24:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ast.h"
#include "../../headers/minishell.h"

/*
	Create a new token
*/
t_tk	*tk_new(enum e_type type, char *data)
{
	t_tk	*new;

	new = malloc(sizeof(t_tk));
	if (new)
	{
		(new->type) = type;
		(new->data) = data;
		(new->prev) = NULL;
		(new->left) = NULL;
		(new->right) = NULL;
		return (new);
	}
	return (NULL);
}

/*
	Recursively iterate the tree from left to right 
*/
void	tk_iter(t_tk *root, void (*f)(t_tk *, int), int depth)
{
	if (!root)
		return ;
	tk_iter(root->left, f, depth + 1);
	f(root, depth);
	tk_iter(root->right, f, depth + 1);
}

int		tk_is_rd(enum e_type type)
{
	return (type == E_LSR || type == E_LLSR || type == E_GRT || type == E_GGRT);
}

/* ----- TEST  ------- */

void	tk_print(t_tk *tk, int depth)
{
	while (depth-- > 0)
		printf("\t");
	printf("(%d,%s)\n", (int)(tk->type), (tk->data));
}

int	main(void)
{
	char	*s[] = {"< in", "wc", "echo", "cat"};
	t_tk	*tree;

	tree = NULL;
	tk_add(&tree, tk_new(E_LSR, s[0]));
	tk_add(&tree, tk_new(E_CMD, s[1]));
	tk_add(&tree, tk_new(E_PIPE, NULL));
	tk_add(&tree, tk_new(E_LSR, s[0]));
	tk_add(&tree, tk_new(E_CMD, s[2]));
	tk_add(&tree, tk_new(E_PIPE, NULL));
	tk_add(&tree, tk_new(E_CMD, s[3]));
	
	tk_iter(tree, tk_print, 0);
	return (0);
}
