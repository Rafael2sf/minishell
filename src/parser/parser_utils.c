/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:30:24 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/15 11:48:11 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

int	ms_parse_error(int code)
{
	perror("minishell: ");
	return (code);
}

char	**ms_parse_paths(char ***env)
{
	char	*vpath;
	char	**paths;

	paths = NULL;
	vpath = ft_getenv("PATH", env);
	if (vpath)
		paths = ft_split(vpath, ": \t\v\b\r\n");
	return (paths);
}
