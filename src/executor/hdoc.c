/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:11:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/01 12:10:16 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

static void	ms_read_heredoc(const char *delimitir, int dlen, int fd);

int	ms_heredoc(const char *delimitir)
{
	int		p[2];
	int		dlen;

	dlen = ft_strlen(delimitir);
	if (dlen < 0)
		return (-1);
	if (pipe(p) < 0)
		return (-1);
	ms_read_heredoc(delimitir, dlen, p[1]);
	close(p[1]);
	return (p[0]);
}

static void	ms_read_heredoc(const char *delimitir, int dlen, int fd)
{
	char	*line;
	int		len;
	int		j;

	while (1)
	{
		j = 0;
		write(1, "> ", 2);
		line = ft_getnl(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimitir, dlen) == 0
			&& line[dlen] == '\n')
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
		free(line);
	}
}
