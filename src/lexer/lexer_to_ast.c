/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:10 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 12:35:21 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "lexer.h"

static t_ast	*ms_create_token_cmd(t_ast **root, char *s, int size, char c);
static t_ast	*ms_create_token_any(char *s, int size, t_type t);
static int		tk_merge(t_ast *root, char *s, int size, char c);

int	ms_create_token(t_ast **root, t_type type, char *s, int size)
{
	t_ast	*new_t;

	new_t = NULL;
	if (type == E_CMD)
		new_t = ms_create_token_cmd(root, s, size, s[size]);
	else
		new_t = ms_create_token_any(s, size, type);
	if (!new_t)
		return (ms_lexer_error(-1, '-', 1));
	ast_add(root, new_t);
	return (0);
}

static t_ast	*ms_create_token_cmd(t_ast **root, char *s, int size, char c)
{
	t_ast	*base;
	char	**cmd;

	base = NULL;
	if (*root && (*root)->type == E_CMD)
		base = *root;
	else if (*root && (*root)->type == E_PIPE && (*root)->right)
		base = (*root)->right;
	if (base)
	{
		if (tk_merge(base, s, size, s[size]) != 0)
			return (NULL);
		return (base);
	}
	else
	{
		s[size] = 0;
		cmd = ms_split(s, ' ');
		s[size] = c;
		if (!cmd)
			return (NULL);
	}
	return (tk_new_token(E_CMD, cmd));
}

static t_ast	*ms_create_token_any(char *s, int size, t_type t)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	if (s)
	{
		c = s[size];
		s[size] = 0;
		tmp = ft_strndup(s, size);
		s[size] = c;
		if (!tmp)
			return (NULL);
	}
	return (tk_new_token(t, tmp));
}

static int	tk_merge(t_ast *root, char *ref, int size, char c)
{
	char	**tmp;
	char	**new;

	ref[size] = 0;
	new = ms_split(ref, ' ');
	ref[size] = c;
	if (!new)
		return (-1);
	tmp = ptr_ptr_join((char **)root->data, new);
	if (!tmp)
	{
		ptr_ptr_free((void **)new);
		return (-1);
	}
	(root->data) = tmp;
	return (0);
}
