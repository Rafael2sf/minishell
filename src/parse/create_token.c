/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:10 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/28 10:18:50 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static t_ast	*ms_create_token_cmd(t_ast **root, char *str, int size);
static int		tk_merge(t_ast **root, char *ref, int ref_len);

int	ms_create_token(t_ast **root, enum e_type type, const char *ref, int size)
{
	t_ast	*new_t;
	char	*str;
	int		ret;

	ret = 0;
	new_t = NULL;
	str = strndup(ref, size); // Using forbidden function
	if (!str)
	{
		perror("minishell: ");
		return (-1);
	}
	if (type == E_CMD)
		new_t = ms_create_token_cmd(root, str, size);
	else
		new_t = tk_new_token(type, str);
	if (!new_t)
	{
		free(str);
		perror("minishell: ");
		return (-1);
	}
	if (ret == 0 && new_t != *root)
		ret = ast_add(root, new_t);
	if (ret == -1)
		perror("minishell: ");
	return (ret);
}

static t_ast	*ms_create_token_cmd(t_ast **root, char *str, int size)
{
	t_ast	*new_t;
	char	**cmd;

	if (*root && (*root)->type == E_CMD)
	{
		if (tk_merge(root, str, size) != 0)
		{
			printf("ERROR 1\n"); // Merge this two line
			return (NULL);
		}
		return (*root);
	}
	else
	{
		cmd = ms_split(str, ' ');
		if (!cmd)
			return (NULL);
		new_t = tk_new_token(E_CMD, cmd);
	}
	return (new_t);
}

/*
	Strjoin both data, set type to given type and free old memory
*/
static int	tk_merge(t_ast **root, char *ref, int ref_len)
{
	char	**new;
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)((*root)->data);
	while (arr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (-1);
	new[i + 1] = NULL;
	new[i] = ref;
	while (--i >= 0)
		new[i] = arr[i];
	free(arr);
	((*root)->data) = (void *)(new);
	return (0);
}
