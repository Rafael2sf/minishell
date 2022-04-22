/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:09:01 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/22 11:04:25 by rafernan         ###   ########.fr       */
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
# include <errno.h>
# include <stdbool.h>

# include "../libft/libft.h"

typedef int	(*t_bultinf) (char **, int, int *, char ***);

typedef enum e_type
{
	E_UNDEF,
	E_CMD,
	E_PIPE,
	E_LSR,
	E_LLSR,
	E_GRT,
	E_GGRT
}	t_type;

enum
{
	SI_IGN,
	SI_HDOC,
	SI_RLINE,
	SI_DFL
};

/*
	Abstract syntax tree
	note:	data is a char ** for E_CMD
					a char * for redirections
					and NULL for the rest
*/
typedef struct s_ast
{
	t_type			type;
	void			*data;
	pid_t			pid;
	int				p[2];
	t_bultinf		func;
	struct s_ast	*prev;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

// Useful variable structure for lexer and parser */
typedef struct s_pvars
{
	int	quote;
	int	dquote;
	int	start;
	int	end;
}		t_pvars;

/* Minishell structure */
typedef struct s_mshell
{
	char	*prompt;
	t_ast	*tokens;
	int		stat;
	char	**env;
	char	**paths;
	bool	sig_call;
}	t_mshell;

/*  readline */
void	rl_replace_line(const char *text, int clear_undo);

/* Builtin commands */
int		ft_cd(char **input, int fd, int *stat, char ***env);
int		ft_unset(char **input, int fd, int *stat, char ***env);
int		ft_export(char **input, int fd, int *stat, char ***env);
int		ft_echo(char **input, int fd, int *stat, char ***env);
int		ft_env(char **input, int fd, int *stat, char ***env);
int		ft_exit(char **input, int fd, int *stat, char ***env);
int		ft_pwd(char **input, int fd, int *stat, char ***env);

/* AST functionality */
void	ast_free(t_ast **root);
int		ast_iter_pre(t_ast *root, int (*f)(t_ast *, void *), bool r, void *p);
int		ast_iter_in(t_ast *root, int (*f)(t_ast *, void *), bool r, void *p);
int		ast_iter_pos(t_ast *root, int (*f)(t_ast *, void *), bool r, void *p);

/* Functions */
int		ms_lexer(t_ast **root, char *line);
int		ms_parser(t_mshell *shell);
int		ms_executor(t_mshell *shell);

/* Utils */
char	*ms_expand(char *str, t_mshell *shell, int ign_quotes);
char	**ms_split(char const *s, char c);
void	ms_exit(t_mshell *shell);
void	ptr_ptr_free(char **ptr);
int		ptr_ptr_len(char **s);
char	**ptr_ptr_dup(char **env);
char	**ptr_ptr_join(char **a, char **b);
char	*ft_getenv(char *env_var, char **env);
int		nbr_len(int n);
int		tk_is_last(t_ast *tk);
void	ms_clean(t_mshell *shell);
void	werror(char *s);

/* Signal handling */
void	call_sigact(char act_choice, t_mshell *shell);

/* TTY Attributes */
void	prep_terms(struct termios *term, struct termios *term2,
			t_mshell *shell);
void	attr_setting(struct termios *term, t_mshell *shell);

#endif
