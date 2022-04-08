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

static t_ast	*ms_create_token_cmd(t_ast **root, char *s, int size, char c);
static t_ast	*ms_expand_cmd(t_ast *new_t);
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
		return (ms_parse_error(-1, '-', 1));
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
		return (ms_expand_cmd(base));
	}
	else
	{
		s[size] = 0;
		cmd = altered_split(s, ' ');
		s[size] = c;
		if (!cmd)
			return (NULL);
	}
	return (ms_expand_cmd(tk_new_token(E_CMD, cmd)));
}

static t_ast	*ms_expand_cmd(t_ast *new_t)
{
	char	**ref;
	char	*tmp;
	int		i;

	i = -1;
	if (!new_t)
		return (NULL);
	ref = (new_t->data);
	while (ref[++i])
	{
		tmp = ms_expand(ref[i]);
		if (!tmp)
		{
			ft_free_m(ref);
			free(new_t);
			return (NULL);
		}
		if (tmp != ref[i])
		{
			free(ref[i]);
			ref[i] = tmp;
		}
	}
	return (new_t);
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
		tmp = ms_expand(s);
		s[size] = c;
		if (!tmp)
			return (NULL);
		if (tmp == s)
			tmp = ft_strndup(s, size); // forbbiden
	}
	return (tk_new_token(t, tmp));
}

static int	tk_merge(t_ast *root, char *ref, int size, char c)
{
	char	**tmp;
	char	**new;

	ref[size] = 0;
	new = altered_split(ref, ' ');
	ref[size] = c;
	if (!new)
		return (-1);
	tmp = ft_strjoin_m((char **)root->data, new);
	if (!tmp)
	{
		ft_free_m(new);
		return (-1);
	}
	(root->data) = tmp;
	return (0);
}
