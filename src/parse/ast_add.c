/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:20:31 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/21 18:25:37 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ast.h"
#include "../../headers/minishell.h"

static t_tk	*tk_add_cmd(t_tk **root, t_tk *new);

t_tk	*tk_add(t_tk **root, t_tk *new)
{
	if (!root || !new)
		return (NULL);
	if (!*root)
	{
		if (tk_is_rd(new->type)) // If is redirection and first
		{
			(*root) = tk_new(E_UNDEF, NULL);
			if (new->type == E_LSR || E_GRT)
				((*root)->left) = new;
			else
				((*root)->right) = new;
		}
		else
			(*root) = new;
		return (new);
	}
	if (new->type == E_CMD || new->type == E_UNDEF)
		return (tk_add_cmd(root, new));
	else if (new->type == E_PIPE) // Always add on top
		tk_add_top(root, new);
	// <-- Add and or
	return (tk_add_rd(root, new));
}

t_tk	*tk_add_top(t_tk **root, t_tk *new)
{
	if (!root || !*root || !new)
		return (NULL);
	(new->left) = *root;
	(new->prev) = ((*root)->prev);
	((*root)->prev) = new;
	(*root) = new;
	return (new);
}

static t_tk	*tk_add_cmd(t_tk **root, t_tk *new)
{
	// If pipe
	if (((*root)->type) == E_PIPE && !((*root)->right))
	{
		((*root)->right) = new;
		(new->prev) = ((*root)->right);
		return (new);
	}
	// if command is undef substitute it
	else if (((*root)->type) == E_UNDEF)
	{
		((*root)->type) = E_CMD;
		((*root)->data) = (new->data);
		free(new);
		return ((*root)->right);
	}
	else if ((*root)->right)
		return (tk_add_cmd(&(*root)->right, new));
	return (NULL);
}
