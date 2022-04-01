#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# define t_uint	unsigned int

enum e_type
{
	E_UNDEF,
	E_CMD,
	E_PIPE,
	E_LSR,
	E_LLSR,
	E_GRT,
	E_GGRT
};
typedef enum e_type t_type;

/*
	Abstract syntax tree
	note:	data is a char ** for E_CMD
					a char * for redirections
					and NULL for the rest
*/
typedef struct s_ast
{
	enum e_type		type;
	void			*data;
	pid_t			pid;
	int				p[2];
	struct s_ast	*prev;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

// Variables for parsing
typedef struct s_pvars
{
	int	quote;
	int	dquote;
	int	start;
	int	end;
}		t_pvars;

void	pvars_init(t_pvars *v);
t_ast	*tk_new_token(t_type type, void *ref);
int		tk_is_rd(t_type type);

int		ast_add(t_ast **root, t_ast *new_token);
int		ast_add_top(t_ast **root, t_ast *new_token);
int		ast_add_left(t_ast **root, t_ast *new_token);
int		ast_add_right(t_ast **root, t_ast *new_token);
void	ast_iter(t_ast *root, void (*f)(void *));

int		ft_is(char c, char const *set);
char	**ms_split(char const *s, char c);

int		ms_parse(t_ast **root, char *line);
int		ms_parse_error(int code, char c, bool use_perror);
int		ms_parse_token(t_ast **root, char *line, t_pvars *v);
int		ms_create_token(t_ast **root, t_type type, char *ref, int size);
void	ms_parse_quotes(char c, t_pvars *v);

int		ft_strlen_m(char **s);
int		ft_free_m(char **s);
int		ft_memcpy_m(char **d, char **s);
char	**ft_strjoin_m(char **a, char **b);
char	*ms_expand(char *str);

#endif /* AST_H */
