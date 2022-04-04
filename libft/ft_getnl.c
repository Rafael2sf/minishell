/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:12:33 by rafernan          #+#    #+#             */
/*   Updated: 2021/12/09 10:51:54 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_getline(char **rdbuff, char **buff, char *strg, size_t rdbl)
{
	char	*line;
	size_t	bufflen;

	bufflen = ft_strlen(*buff);
	line = (char *)malloc(sizeof(char) * bufflen + rdbl + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, (*buff), bufflen);
	ft_memcpy(line + bufflen, (*rdbuff), rdbl);
	line[bufflen + rdbl] = '\0';
	bufflen = 0;
	while ((*rdbuff)[rdbl])
		strg[bufflen++] = (*rdbuff)[rdbl++];
	strg[bufflen] = '\0';
	if (*buff)
		free(*buff);
	return (line);
}

static char	*gnl_read(int fd, char **rdbuff, char **buff, char *strg)
{
	char	*tmp;
	ssize_t	bytes;

	tmp = *buff;
	while (1)
	{
		bytes = read(fd, (*rdbuff), BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
			return (*buff);
		(*rdbuff)[bytes] = '\0';
		tmp = ft_strchr(*rdbuff, '\n');
		if (tmp)
			return (gnl_getline(rdbuff, buff, strg, tmp - (*rdbuff) + 1));
		tmp = ft_strjoin(*buff, *rdbuff);
		if (*buff)
			free(*buff);
		if (!tmp)
			return (NULL);
		(*buff) = tmp;
	}
}

static char	*gnl_strgl(char *strg, size_t slen)
{
	char	*line;
	size_t	i;

	line = (char *)malloc(sizeof(char) * slen + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, strg, slen);
	line[slen] = '\0';
	i = 0;
	while (strg[slen])
		strg[i++] = strg[slen++];
	strg[i] = '\0';
	return (line);
}

char	*ft_getnl(int fd)
{
	static char	strg[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*rdbuf;
	char		*buff;

	buff = NULL;
	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	buff = ft_strchr(strg[fd], '\n');
	if (!buff)
	{
		if (strg[fd][0])
			buff = ft_strdup(strg[fd]);
		strg[fd][0] = '\0';
		rdbuf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!rdbuf)
			return (NULL);
		line = gnl_read(fd, &rdbuf, &buff, strg[fd]);
		free(rdbuf);
		return (line);
	}
	return (gnl_strgl(strg[fd], buff - strg[fd] + 1));
}
