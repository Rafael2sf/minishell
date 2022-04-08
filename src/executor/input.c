/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:08:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/08 18:46:56 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/executor.h"

static int	ms_epipe(void);
static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error);
static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error);
static int	ms_set_input(int i_fd, bool error);

int	ms_get_input(t_ast *cur)
{
	t_ast	*tmp;
	bool	error;
	int		fd;

	fd = -1;
	tmp = cur;
	error = false;
	if (!tmp->left)
	{
		if (tmp->prev && tmp->prev->left != tmp) // If first wiht pipe
			fd = (cur->prev->p)[0]; 
		else
			fd = dup(STDIN_FILENO);
		return (fd);
	}
	if (tmp->prev && tmp->prev->left != tmp)
		close((cur->prev->p)[0]);
	while (tmp->left)
		tmp = (tmp->left);
	ms_get_llsr(tmp, &fd, &error);
	ms_get_lsr(tmp, &fd, &error);
	return (ms_set_input(fd, error));
}

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error)
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
			if (tmp->prev->type == E_CMD || tmp->prev->type == E_UNDEF)
				(*i_fd) = fd;
			else if (fd > 2)
				close(fd);
		}
		tmp = (tmp->prev);
	}
}

static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error)
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
			if (tmp->prev->type == E_CMD || tmp->prev->type == E_UNDEF)
				(*i_fd) = fd;
			else if (fd > 2)
				close(fd);
		}
		tmp = (tmp->prev);
	}
}

static int	ms_set_input(int i_fd, bool error)
{	
	if (error == true)
	{
		if (i_fd > 2)
			close(i_fd);
		i_fd = ms_epipe();
	}
	return (i_fd);
}

static int	ms_epipe(void)
{
	int	p[2];

	if (pipe(p) == -1)
		return (-1);
	close(p[1]);
	return (p[0]);
}
