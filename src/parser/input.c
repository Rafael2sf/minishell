/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:08:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/14 12:36:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static void	ms_get_llsr(t_ast *tmp, int *i_fd, bool *error, t_mshell *shell);
static void	ms_get_lsr(t_ast *tmp, int *i_fd, bool *error);

int	ms_parse_input(t_ast *cur, t_mshell *shell)
{
	t_ast	*tmp;
	bool	error;
	int		fd;
	struct sigaction	act;


	fd = -1;
	tmp = cur;
	error = false;
	prep_act(&act, 'i');
		if (sigaction(SIGINT, &act, NULL) == -1 ||
        sigaction(SIGQUIT, &act, NULL) == -1)
    	{
       		perror("Error in sigaction");
        	return (errno);
	}
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
	ms_get_llsr(tmp, &fd, &error, shell);
	ms_get_lsr(tmp, &fd, &error);
	if (error) //Now what? error fica true com rececao de CTRL + C, para onde vai a seguir?
	{
		if (fd > 2)
			close(fd);
		return (-1);
	}
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
