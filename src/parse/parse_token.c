/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:10 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/23 18:01:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

int	ms_create_token(t_tk **root, enum e_type type, const char *ref, int size)
{
	t_tk	*new;
	char	*p;

	p = NULL;
	printf("%d %d\n", (int)type, size);
	if (type != E_PIPE)
	{
		p = malloc(sizeof(char) * size);
		if (!p)
			return (-1);
		memcpy(p, ref, size + 1); // Using memcpy unallowed
		p[size] = '\0';
	}
	new = tk_new_token(type, p);
	if (!new)
	{
		free(p);
		return (-1);
	}
	if (ast_add(root, new) != 0)
	{
		printf("something went wrong -- parse_token.c l:34\n");
	}
	return (0);
}
