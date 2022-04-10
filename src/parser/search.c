/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:24:23 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/10 17:22:26 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static char	*ms_find_file(char **cmd, char **paths);
static int	ms_check_file(char *filepath);
static char	*ms_srchfp(char *fname, char **paths);
static char	*ms_strpath(char *path, const char *file);

char	*ms_parse_cmd(char **cmd, char **paths)
{
	char	*fp;

	fp = NULL;
	if (!cmd || !*cmd || !**cmd)
	{
		ft_putstr(STDERR_FILENO, "command not found\n");
		return (NULL);
	}
	fp = ms_find_file(cmd, paths);
	if (!fp)
		return (NULL);
	if (*cmd != fp)
		free(*cmd);
	*cmd = fp;
	return (*cmd);
}

static char	*ms_find_file(char **cmd, char **paths)
{
	char	*fp;
	int		i;

	i = 0;
	fp = NULL;
	while ((*cmd)[i] != '/' && (*cmd)[i])
		i++;
	if ((*cmd)[i] == '/' && ms_check_file(*cmd) == 0)
		fp = *cmd;
	else if ((*cmd)[i] == '/')
	{
		write(STDERR_FILENO, "minishell: ", 12);
		perror(*cmd); // Not writing expected error try "../"
	}
	else
		fp = ms_srchfp(*cmd, paths);
	return (fp);
}

static int	ms_check_file(char *filepath)
{
	struct stat	file_stat;

	if (!filepath)
		return (-1);
	stat(filepath, &file_stat);
	if (access(filepath, F_OK | X_OK) == 0 && S_ISREG(file_stat.st_mode))
		return (0);
	return (-1);
}

static char	*ms_srchfp(char *fname, char **paths)
{
	char	*fp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		fp = ms_strpath(paths[i], fname);
		if (ms_check_file(fp) == 0)
			return (fp);
		if (fp)
			free(fp);
		i++;
	}
	ft_putstr(STDERR_FILENO, "minishell: ");
	ft_putstr(STDERR_FILENO, fname);
	ft_putstr(STDERR_FILENO, ": command not found\n");
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
