/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:09:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:44:13 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

# include "parse.h"
# include "../libft/libft.h"

typedef struct	s_mshell
{
	char	*prompt;
	t_ast	*tokens;
	int		stat;
	char	**env;
}	t_mshell;

char	**altered_split(char const *s, char c);
char	**change_shlvl(char ***env);
void	ptr_ptr_free(void **ptr);
char	**creat_copy(char **env);

#endif
