/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:24:23 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/22 10:26:17 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ms_find_file(char **cmd, t_ast *tk, t_mshell *shell);
static int	ms_check_file(char *filepath, int check_dir,
				t_ast *tk, t_mshell *shell);
static char	*ms_srchfp(char *fname, t_ast *tk, t_mshell *shell);
static char	*ms_strpath(char *path, const char *file);

char	*ms_parse_cmd(char **cmd, t_ast *tk, t_mshell *shell)
{
	char	*fp;

	fp = NULL;
	if (!cmd || !*cmd || !**cmd)
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		if (tk_is_last(tk))
			(shell->stat) = 127;
		return (NULL);
	}
	if ((*cmd)[0] == '.' && !(*cmd)[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n \
.: usage: . filename [arguments]\n", STDERR_FILENO);
		if (tk_is_last(tk))
			(shell->stat) = 2;
		return (NULL);
	}
	fp = ms_find_file(cmd, tk, shell);
	if (!fp)
		return (NULL);
	if (*cmd != fp)
		free(*cmd);
	*cmd = fp;
	return (*cmd);
}

static char	*ms_find_file(char **cmd, t_ast *tk, t_mshell *shell)
{
	int		i;
	int		v;

	i = 0;
	while ((*cmd)[i] && (*cmd)[i] != '/')
		i++;
	v = ms_check_file(*cmd, 1, tk, shell);
	if (v == 1)
		return (NULL);
	if (v == 0)
		return (*cmd);
	if ((*cmd)[i] == '/')
	{
		werror(*cmd);
		if (tk_is_last(tk))
			(shell->stat) = 127;
		return (NULL);
	}
	return (ms_srchfp(*cmd, tk, shell));
}

static int	ms_check_file(char *filepath, int check_dir,
	t_ast *tk, t_mshell *shell)
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
			ft_putstr_fd(filepath, STDERR_FILENO);
			write(STDERR_FILENO, " : is a directory\n", 18);
			if (tk_is_last(tk))
				(shell->stat) = 126;
			return (1);
		}
	}
	else
		return (-1);
	return (0);
}

static char	*ms_srchfp(char *fname, t_ast *tk, t_mshell *shell)
{
	char	*fp;
	int		i;

	i = 0;
	while ((shell->paths) && (shell->paths)[i])
	{
		fp = ms_strpath((shell->paths)[i], fname);
		if (ms_check_file(fp, 0, tk, shell) == 0)
			return (fp);
		if (fp)
			free(fp);
		i++;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(fname, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (tk_is_last(tk))
		(shell->stat) = 127;
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
