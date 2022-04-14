/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:11:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/13 16:22:02 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

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
	}
}
