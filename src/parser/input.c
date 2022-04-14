/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:08:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/13 15:34:10 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error);
static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error);

int	ms_parse_input(t_ast *cur)
{
	t_ast	*tmp;
	bool	error;
	int		fd;

	fd = -1;
	tmp = cur;
	error = false;
	if (!tmp->left)
	{
		if (tmp->prev && tmp->prev->left != tmp)
			fd = (cur->prev->p)[0];
		else
			fd = dup(STDIN_FILENO);
		return (fd);
	}
	if (tmp->prev && tmp->prev->left != tmp)
		close((cur->prev->p)[0]);
	ms_get_llsr(tmp, &fd, &error);
	ms_get_lsr(tmp, &fd, &error);
	if (error)
	{
		if (fd > 2)
			close(fd);
		return (-1);
	}
	return (fd);
}

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error)
{
	int	fd;

	while (tmp->left)
		tmp = (tmp->left);
	while (tmp->type == E_LSR || tmp->type == E_LLSR)
	{
		if (tmp->type == E_LLSR)
		{
			fd = ms_heredoc((char *)tmp->data);
			if (fd == -1)
			{
				perror("minishell: ");
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

	while (tmp->left)
		tmp = (tmp->left);
	while (tmp->type == E_LSR || tmp->type == E_LLSR)
	{
		if (tmp->type == E_LSR)
		{
			fd = open((char *)tmp->data, O_RDONLY, 0644);
			if (fd == -1)
			{
				(*error) = true;
				ft_putstr(2, "minishell: ");
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
