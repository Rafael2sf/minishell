/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:24:23 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/13 11:34:40 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "parser.h"

static char	*ms_find_file(char **cmd, char **paths);
static int	ms_check_file(char *filepath, int check_dir);
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
	if ((*cmd)[0] == '.' && !(*cmd)[1])
	{
		ft_putstr(STDERR_FILENO, "minishell: .: filename argument required\n \
.: usage: . filename [arguments]\n");
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
	int		i;
	int		v;

	i = 0;
	while ((*cmd)[i] && (*cmd)[i] != '/')
		i++;
	v = ms_check_file(*cmd, 1);
	if (v == 1)
		return (NULL);
	if (v == 0)
		return (*cmd);
	if ((*cmd)[i] == '/')
	{
		ft_putstr(STDERR_FILENO, "minishell: ");
		perror(*cmd);
		return (NULL);
	}
	return (ms_srchfp(*cmd, paths));
}

static int	ms_check_file(char *filepath, int check_dir)
{
	struct stat	file_stat;

	if (!filepath)
		return (-1);
	stat(filepath, &file_stat);
	if (access(filepath, F_OK | X_OK) == 0)
	{
		if (check_dir && S_ISREG(file_stat.st_mode) == 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			ft_putstr(STDERR_FILENO, filepath);
			write(STDERR_FILENO, " : Is a directory\n", 18);
			return (1);
		}
	}
	else
		return (-1);
	return (0);
}

static char	*ms_srchfp(char *fname, char **paths)
{
	char	*fp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		fp = ms_strpath(paths[i], fname);
		if (ms_check_file(fp, 0) == 0)
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
