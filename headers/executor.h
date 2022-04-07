#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct	s_exc
{
	t_ast	*token;
	int		i_fd;
	int		o_fd;
	int		*stat;
	char	**cmd;
	char	**envp;
	char	**paths;
}			t_exc;

int		ms_get_input(t_ast *cur, int *i_fd);
int		ms_get_output(t_ast *cur, int *o_fd);
char	**ms_paths(void);
char	*ms_newcmd(char **cmd, char **paths);
int		ms_heredoc(const char *delimitir);
int		ast_executor(t_ast *tokens, int *wstat, char ***env);

# endif
