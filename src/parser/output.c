/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:59:46 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 18:03:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ms_get_ofiles(t_ast *tmp, int o_fd, bool *error);

int	ms_parse_output(t_ast *cur)
{
	t_ast	*tmp;
	bool	error;
	int		fd;

	fd = -1;
	tmp = cur;
	error = false;
	if (!tmp->right)
	{
		if (tmp->prev && tmp->prev->left == tmp)
			fd = (tmp->prev->p)[1];
		else if (tmp->prev && tmp->prev->prev)
			fd = (tmp->prev->prev->p)[1];
		else
			fd = dup(STDOUT_FILENO);
		return (fd);
	}
	if (tmp->prev && tmp->prev->left == tmp)
		close((cur->prev->p)[1]);
	else if (tmp->prev && tmp->prev->prev)
		close((tmp->prev->prev->p)[1]);
	while (tmp->right)
		tmp = (tmp->right);
	return (ms_get_ofiles(tmp, fd, &error));
}

static int	ms_get_ofiles(t_ast *tmp, int o_fd, bool *error)
{
	int	fd;

	while (tmp->type == E_GRT || tmp->type == E_GGRT)
	{
		if (tmp->type == E_GRT)
			fd = open((char *)tmp->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open((char *)tmp->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			werror((char *)(tmp->data));
			(*error) = true;
			return (-1);
		}
		if (tmp->prev->type == E_CMD || tmp->prev->type == E_UNDEF)
			o_fd = fd;
		else if (fd > 2)
			close(fd);
		tmp = (tmp->prev);
	}
	return (o_fd);
}

/*

		(P)
	(P)		(CMD)
(CMD) 	(CMD)

*/