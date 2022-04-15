/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:08:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/15 17:00:25 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error, t_mshell *shell);
static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error);
static int	fd_returner(t_ast *tmp, int fd, t_ast *cur);

int	ms_parse_input(t_ast *cur, t_mshell *shell)
{
	t_ast				*tmp;
	bool				error;
	int					fd;

	fd = -1;
	tmp = cur;
	error = false;
	if (call_sigact('i') == -1)
		return (errno);
	if (!tmp->left)
		return (fd_returner(tmp, fd, cur));
	if (tmp->prev && tmp->prev->left != tmp)
		close((cur->prev->p)[0]);
	ms_get_llsr(tmp, &fd, &error, shell);
	ms_get_lsr(tmp, &fd, &error);
	if (error)
	{
		if (fd > 2)
			close(fd);
		return (-1);
	}
	return (fd);
}

static int	fd_returner(t_ast *tmp, int fd, t_ast *cur)
{
	if (tmp->prev && tmp->prev->left != tmp)
		fd = (cur->prev->p)[0];
	else
		fd = dup(STDIN_FILENO);
	return (fd);
}

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error, t_mshell *shell)
{
	int	fd;

	while (tmp->left)
		tmp = (tmp->left);
	while (tmp->type == E_LSR || tmp->type == E_LLSR)
	{
		if (tmp->type == E_LLSR)
		{
			fd = ms_heredoc((char *)tmp->data, shell);
			if (fd == -1)
			{
				perror("minishell: ");
				(*error) = true;
			}
			else if (fd == -2)
				(*error) = true;
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
