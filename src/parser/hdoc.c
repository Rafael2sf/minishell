/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:11:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/14 12:50:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static void	ms_read_heredoc(const char *delimitir, int dlen, int fd);

int	ms_heredoc(const char *delimitir, t_mshell *shell)
{
	int		p[2];
	int		dlen;
	pid_t	pid;
	struct sigaction	act;


	dlen = ft_strlen(delimitir);
	if (dlen < 0)
		return (-1);
	if (pipe(p) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		//ptr_ptr_free((void **)(*shell->env));
		//ast_free(&(shell->tokens));
		prep_act(&act, '<');
		if (sigaction(SIGINT, &act, NULL) == -1 ||
        sigaction(SIGQUIT, &act, NULL) == -1)
    	{
       		perror("Error in sigaction");
        	return (errno);
		}
		close(p[0]);
		ms_read_heredoc(delimitir, dlen, p[1]);
		clear_history();
		close(p[1]);
		exit(0);
	}
	else
	{

		close(p[1]);
		waitpid(pid, &shell->stat, 0);
		printf("%d\n", shell->stat);
	}
	if (shell->stat == 256)
	{
		shell->sig_call = true;
		return (-2);
	}
	return (p[0]);
}

static void	ms_read_heredoc(const char *delimitir, int dlen, int fd)
{
	char	*line;
	int		len;
	char	*tmp;
	
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		int a = 0;
		tmp = ms_expand(line, &a);
		if (tmp && line != tmp)
		{
			free(line);
			line = tmp;
		}
		if (ft_strncmp(line, delimitir, dlen) == 0
			&& line[dlen] == '\0')
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		if (write(fd, line, sizeof(char) * len) == -1)
		{
			perror("");
			break ;
		}
		write(fd, "\n", 1);
		free(line);
		write(fd, "\n", 1);
	}
}
