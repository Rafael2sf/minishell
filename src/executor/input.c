/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:08:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/04 16:57:20 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

static int	ms_epipe(void);
static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error, t_ast *last);
static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error, t_ast *last);
static int	ms_set_input(int *i_fd, bool error);

int	ms_get_input(t_ast *cur, int *i_fd)
{
	t_ast	*tmp;
	t_ast	*last;
	bool	error;
	
	tmp = cur;
	error = false;
	if (tmp->type == E_PIPE)
		tmp = (tmp->right);
	last = tmp->left;
	if (!tmp->left)
	{
		if (cur->type == E_PIPE)
			(*i_fd) = (cur->p)[0];
		else
			(*i_fd) = dup(STDIN_FILENO);
		return (0);
	}
	while (tmp->left)
		tmp = (tmp->left);
	ms_get_llsr(tmp, i_fd, &error, last);
	ms_get_lsr(tmp, i_fd, &error, last);
	return (ms_set_input(i_fd, error));
}

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error, t_ast *last)
{
	int	fd;
	
	while (tmp->type == E_LSR || tmp->type == E_LLSR)
	{
		if (tmp->type == E_LLSR)
		{
			fd = ms_heredoc((char *)tmp->data);
			if (fd == -1)
			{
				perror("");
				(*error) = true;
			}
			if (tmp == last)
				(*i_fd) = fd;
			else
				close(fd);
		}
		tmp = (tmp->prev);
	}
}

static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error, t_ast *last)
{
	int	fd;
	
	while (tmp->type == E_LSR || tmp->type == E_LLSR)
	{
		if (tmp->type == E_LSR)
		{
			fd = open((char *)tmp->data, O_RDONLY, 0644);
			if (fd == -1)
			{
				(*error) = true;
				perror((char *)tmp->data);
			}
			if (tmp == last)
				(*i_fd) = fd;
			else
				close(fd);
		}
		tmp = (tmp->prev);
	}
}

static int	ms_set_input(int *i_fd, bool error)
{	
	if (error == true)
	{
		if (*i_fd > 0)
			close(*i_fd);
		*i_fd = ms_epipe();
		if (*i_fd == -1)
			return (-1);
		return (0);
	}
	return (0);
}

static int	ms_epipe(void)
{
	int	p[2];

	if (pipe(p) == -1)
		return (-1);
	close(p[1]);
	return (p[0]);
}
