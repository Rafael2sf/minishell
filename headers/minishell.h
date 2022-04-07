/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:09:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/07 11:10:54 by daalmeid         ###   ########.fr       */
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

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct	s_mshell
{
	char	*prompt;
	t_ast	*tokens;
	int		stat;
	char	***env;
}	t_mshell;

void	tk_free(void *tk_ptr);
void	ast_print(t_ast *root, int depth);

char	**altered_split(char const *s, char c);
char	**change_shlvl(char ***env);
void	ptr_ptr_free(void **ptr);
char	**creat_copy(char **env);
char	**export_at_start_process(char **env);

#endif
