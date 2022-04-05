/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:59:46 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/05 10:19:59 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/executor.h"

static int	ms_get_ofiles(t_ast *tmp, int *o_fd, bool *error);

int	ms_get_output(t_ast *cur, int *o_fd)
{
	t_ast	*tmp;
	bool	error;

	tmp = cur;
	error = false;
	if (cur->prev)
		pipe(cur->prev->p);
	if (tmp->type == E_PIPE)
		tmp = (tmp->right);
	if (!tmp->right)
	{
		if (cur->prev)
			(*o_fd) = (cur->prev->p)[1];
		else
			(*o_fd) = dup(STDOUT_FILENO);
		return (0);
	}
	while (tmp->right)
		tmp = (tmp->right);
	return (ms_get_ofiles(tmp, o_fd, &error));
}

static int	ms_get_ofiles(t_ast *tmp, int *o_fd, bool *error)
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
			perror((char *)(tmp->data));
			(*error) = true;
			return (-1);
		}
		if (tmp->prev->type == E_CMD || tmp->prev->type == E_UNDEF)
			(*o_fd) = fd;
		else
			close(fd);
		tmp = (tmp->prev);
	}
	return (0);
}
