/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_rd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:35:43 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/21 18:25:11 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ast.h"
#include "../../headers/minishell.h"

static t_tk	*tk_add_rd_in(t_tk **root, t_tk *new);
static t_tk	*tk_add_rd_out(t_tk **root, t_tk *new);

t_tk	*tk_add_rd(t_tk **root, t_tk *new)
{
	if (new->type == E_LSR || new->type == E_LLSR)
		return (tk_add_rd_in(root, new));
	else
		return (tk_add_rd_out(root, new));
}

static t_tk	*tk_add_rd_in(t_tk **root, t_tk *new) // Simplify ?
{
	if (((*root)->type) == E_CMD)
	{
		(new->prev) = *root;
		if ((*root)->left->left)
		{
			(new->left) = ((*root)->left->left);
			(new->left->left->prev) = new;
		}
		((*root)->left) = new;
		return (new);
	}
	else if (((*root)->type) == E_PIPE)
	{
		if (!((*root)->right))
		{
			((*root)->right) = tk_new(E_UNDEF, NULL);
			((*root)->right->prev) = (*root);
			((*root)->right->left) = new;
			(new->prev) = ((*root)->right) ;
			return (new);
		}
		else
		{
			(new->prev) = ((*root)->right) ;
			(new->left) = ((*root)->right->left);
			((*root)->right->left) = new;
			(new->left->prev) = new;
			return (new);
		}
	}
	return (NULL);
}

static t_tk	*tk_add_rd_out(t_tk **root, t_tk *new) // In reversed ...
{
	(void)(root);
	(void)(new);
	return (NULL);
}

/*

cmd (case 0)

P		(case 1)
new undef on right
add

P
	cmd (case 2)
add

*/
