/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:01:22 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/19 14:32:34 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../lexer/lexer.h"

/*
	Recursively iterate the tree
*/

int	ast_iter_pre(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	t_mshell	*shell;

	shell = (t_mshell *)(ptr);
	if (!root)
		return (0);
	else if (shell && shell->sig_call == true)
		return (-1);
	else if (rev)
	{
		if (f(root, ptr) == -1)
			return (-1);
		ast_iter_pre(root->right, f, rev, ptr);
		ast_iter_pre(root->left, f, rev, ptr);
	}
	else
	{
		if (f(root, ptr) == -1)
			return (-1);
		ast_iter_pre(root->left, f, rev, ptr);
		ast_iter_pre(root->right, f, rev, ptr);
	}
	return (0);
}

int	ast_iter_in(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	t_mshell	*shell;

	shell = (t_mshell *)(ptr);
	if (!root)
		return (0);
	else if (shell && shell->sig_call == true)
		return (-1);
	else if (rev)
	{
		ast_iter_in(root->right, f, rev, ptr);
		if (f(root, ptr) == -1)
			return (-1);
		ast_iter_in(root->left, f, rev, ptr);
	}
	else
	{
		ast_iter_in(root->left, f, rev, ptr);
		if (f(root, ptr) == -1)
			return (-1);
		ast_iter_in(root->right, f, rev, ptr);
	}
	return (0);
}

int	ast_iter_pos(t_ast *root, int (*f)(t_ast *, void *), bool rev, void *ptr)
{
	t_mshell	*shell;

	shell = (t_mshell *)(ptr);
	if (!root)
		return (0);
	else if (shell && shell->sig_call == true)
		return (-1);
	else if (rev)
	{
		ast_iter_pos(root->right, f, rev, ptr);
		ast_iter_pos(root->left, f, rev, ptr);
		if (f(root, ptr) == -1)
			return (-1);
	}
	else
	{
		ast_iter_pos(root->left, f, rev, ptr);
		ast_iter_pos(root->right, f, rev, ptr);
		if (f(root, ptr) == -1)
			return (-1);
	}
	return (0);
}
