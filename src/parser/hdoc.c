/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:11:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/15 17:45:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static void	ms_read_hdoc(const char *dlimit, int dlen, int fd, t_mshell *shell);

void	child_hdoc(const char *delimitir, int dlen, int p[2], t_mshell *shell)
{
	//ptr_ptr_free((void **)(*shell->env));
	//ast_free(&(shell->tokens));
	if (call_sigact('<') == -1)
		exit (errno);
	close(p[0]);
	ms_read_hdoc(delimitir, dlen, p[1], shell);
	clear_history();
	close(p[1]);
	exit(0);
}

int	ms_heredoc(const char *delimitir, t_mshell *shell)
{
	int					p[2];
	int					dlen;
	pid_t				pid;

	dlen = ft_strlen(delimitir);
	if (dlen < 0)
		return (-1);
	if (pipe(p) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
		child_hdoc(delimitir, dlen, p, shell);
	close(p[1]);
	waitpid(pid, &shell->stat, 0);
	if ((shell->stat) == 256)
	{
		(shell->sig_call) = true;
		(shell->stat) = 1;
		return (-2);
	}
	return (p[0]);
}

static void	ms_read_hdoc(const char *dlimit, int dlen, int fd, t_mshell *shell)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		tmp = ms_expand(line, shell);
		if (tmp && line != tmp)
		{
			free(line);
			line = tmp;
		}
		if (ft_strncmp(line, dlimit, dlen) == 0 && line[dlen] == '\0')
		{
			free(line);
			break ;
		}
		if (write(fd, line, sizeof(char) * ft_strlen(line)) == -1)
		{
			perror("");
			break ;
		}
		write(fd, "\n", 1);
		free(line);
	}
}
