/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:01:22 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/08 12:25:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/parse.h"

/*
	Recursively iterate the tree
*/

int	ast_iter_pre(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	static int	ret;

	if (!root || ret == -1)
	{
		ret = 0;
		return (ret);
	}
	else if (rev)
	{
		ret += f(root, ptr);
		ast_iter_pre(root->right, f, rev, ptr);
		ast_iter_pre(root->left, f, rev, ptr);
	}
	else
	{
		ret += f(root, ptr);
		ast_iter_pre(root->left, f, rev, ptr);
		ast_iter_pre(root->right, f, rev, ptr);
	}
	return (ret);
}

int	ast_iter_in(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	static int	ret;

	if (!root || ret == -1)
	{
		ret = 0;
		return (ret);
	}
	else if (rev)
	{
		ast_iter_in(root->right, f, rev, ptr);
		ret += f(root, ptr);
		ast_iter_in(root->left, f, rev, ptr);
	}
	else
	{
		ast_iter_in(root->left, f, rev, ptr);
		ret += f(root, ptr);
		ast_iter_in(root->right, f, rev, ptr);
	}
	return (ret);
}

int	ast_iter_pos(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	static int	ret;

	if (!root || ret == -1)
	{
		ret = 0;
		return (ret);
	}
	else if (rev)
	{
		ast_iter_pos(root->right, f, rev, ptr);
		ast_iter_pos(root->left, f, rev, ptr);
		ret += f(root, ptr);
	}
	else
	{
		ast_iter_pos(root->left, f, rev, ptr);
		ast_iter_pos(root->right, f, rev, ptr);
		ret += f(root, ptr);
	}
	return (ret);
}
