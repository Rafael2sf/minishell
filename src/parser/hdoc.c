/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:11:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 12:22:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static int	ms_read_hdoc(const char *dlimit, int dlen, int fd, t_mshell *shell);
static void	child_hdoc(const char *delm, int dlen, int p[2], t_mshell *shell);

int	ms_heredoc(const char *delimitir, t_mshell *shell)
{
	int			p[2];
	int			dlen;
	pid_t		pid;

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
		if (p[0] > 2)
			close(p[0]);
		(shell->sig_call) = true;
		(shell->stat) = 1;
		return (-1);
	}
	return (p[0]);
}

static void	child_hdoc(const char *delm, int dlen, int p[2], t_mshell *shell)
{
	int			ret;
	struct stat	st;

	if (call_sigact('<') == -1)
	{
		ms_clean(shell);
		exit (errno);
	}
	close(p[0]);
	ret = ms_read_hdoc(delm, dlen, p[1], shell);
	ms_clean(shell);
	close(p[1]);
	if (fstat(STDIN_FILENO, &st) == -1)
		exit(1);
	else if (ret == -1)
		printf("\x1B[A");
	exit (0);
}

static int	ms_read_hdoc(const char *dlimit, int dlen, int fd, t_mshell *shell)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
		if (ft_strncmp(line, dlimit, dlen) == 0 && line[dlen] == '\0')
			break ;
		tmp = ms_expand(line, shell, 1);
		if (tmp && line != tmp)
		{
			free(line);
			line = tmp;
		}
		if (ft_strncmp(line, dlimit, dlen) == 0 && line[dlen] == '\0')
			break ;
		if (write(fd, line, sizeof(char) * ft_strlen(line)) == -1)
			break ;
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	return (0);
}
