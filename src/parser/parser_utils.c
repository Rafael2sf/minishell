/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:30:24 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 18:03:55 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	tk_close_all(t_ast *tk, void *p);

int	ms_parse_error(int code, t_mshell *shell)
{
	ast_iter_in(shell->tokens, tk_close_all, 0, (void *)(shell));
	if (code == -1)
		werror(NULL);
	if (shell->paths)
	{
		ptr_ptr_free((shell->paths));
		(shell->paths) = NULL;
	}
	return (-1);
}

char	**ms_parse_paths(char **env)
{
	char	*vpath;
	char	**paths;

	paths = NULL;
	vpath = ft_getenv("PATH", env);
	if (vpath)
		paths = ft_split(vpath, ": \t\v\b\r\n");
	return (paths);
}
