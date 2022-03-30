/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:10 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/30 12:23:38 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static t_ast	*ms_create_token_cmd(t_ast **root, char *str, int size, char c);
static int		tk_merge(t_ast *root, char *ref, int size, char c);
static char		*ms_get_str(char *ref, int size, t_ast **root, enum e_type type);
static int		ms_perror(int code, char *message);

int	ms_create_token(t_ast **root, enum e_type type, const char *ref, int size)
{
	t_ast	*new_t;
	char	*str;
	
	str = NULL;
	if (type == E_CMD)
		new_t = ms_create_token_cmd(root, (char *)ref, size, ref[size]);
	else
	{
		if (tk_is_rd(type))
		{
			str = strndup(ref, size); // Forbbiden
			if (!str)
				return (-1);
		}
		new_t = tk_new_token(type, str);
	}
	if (!new_t)
	{
		if (str)
			free(str);
		return (ms_perror(-1, "minishell: "));
	}
	if (new_t != *root && ast_add(root, new_t) != 0)
		return (ms_parse_error(-1, '?')); // This should never hapen !
	return (0);
}

static t_ast	*ms_create_token_cmd(t_ast **root, char *ref, int size, char c)
{
	t_ast	*new_t;
	char	**cmd;

	if (*root && (*root)->type == E_CMD)
	{
		if (tk_merge(*root, ref, size, ref[size]) != 0)
			return (NULL);
		return (*root);
	}
	else if (*root && (*root)->type == E_PIPE && (*root)->right)
	{
		if (tk_merge((*root)->right, ref, size, ref[size]) != 0)
			return (NULL);
		return (*root);
	}
	else
	{
		ref[size] = 0;
		cmd = ms_split(ref, ' ');
		ref[size] = c;
		if (!cmd)
			return (NULL);
		new_t = tk_new_token(E_CMD, cmd);
	}
	return (new_t);
}

/*
	Strjoin both data, set type to given type and free old memory
*/
static int	tk_merge(t_ast *root, char *ref, int size, char c)
{
	char	**tmp;
	char	**new;

	ref[size] = 0;
	new = ms_split(ref, ' ');
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

static int	ms_perror(int code, char *message) // Not writing to stderr
{
	perror(message);
	return (code);
}
