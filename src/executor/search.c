/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:24:23 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/04 17:08:48 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

static char	*ms_srchfp(char *fname, char **paths);
static char	*ms_strpath(char *path, const char *file);

char	**ms_paths(void)
{
	char	*vpath;
	char	**paths;

	paths = NULL;
	vpath = getenv("PATH");
	if (vpath)
		paths = ft_split(vpath, ": \t\v\b\r\n");
	return (paths);
}

char	*ms_newcmd(char **cmd, char **paths)
{
	char	*fp;

	if (!cmd || !*cmd || !**cmd)
	{
		ft_putstr(STDERR_FILENO, "command not found\n");
		return (NULL);
	}
	fp = ms_srchfp(*cmd, paths);
	if (!fp)
	{
		ft_putstr(STDERR_FILENO, "command not found: ");
		ft_putstr(STDERR_FILENO, *cmd);
		ft_putchar(STDERR_FILENO, '\n');
		return (NULL);
	}
	if (*cmd != fp)
		free(*cmd);
	*cmd = fp;
	return (*cmd);
}

static char	*ms_srchfp(char *fname, char **paths)
{
	char	*fp;
	int		i;

	i = 0;
	if ((ft_strncmp(fname, "./", 2) == 0  || fname[0] == '/') 
		&& access(fname, F_OK | X_OK) == 0)
		return (fname);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		fp = ms_strpath(paths[i], fname);
		if (access(fp, F_OK | X_OK) == 0)
			return (fp);
		if (fp)
			free(fp);
		i++;
	}
	return (NULL);
}

static char	*ms_strpath(char *path, const char *file)
{
	char	*new;
	int		extra;
	int		plen;
	int		flen;

	extra = 0;
	plen = ft_strlen(path);
	flen = ft_strlen(file);
	if (file[0] != '/')
		extra++;
	new = malloc(sizeof(char) * (plen + flen + extra + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, path, plen);
	if (extra == 1)
		new[plen] = '/';
	ft_memcpy(new + plen + extra, file, flen);
	new[plen + flen + extra] = '\0';
	return (new);
}
