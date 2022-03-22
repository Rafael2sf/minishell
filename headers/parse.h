#ifndef AST_H
# define AST_H

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

// Abstract syntax tree
typedef struct s_tk
{
	enum e_type	type;
	char		*data;
	struct s_tk	*prev;
	struct s_tk	*left;
	struct s_tk	*right;
}	t_tk;

typedef struct s_pvars
{
	int	quote;
	int	dquote;
	int	word_start;
	int	word_end;
	int	brackets;
}	t_pvars;

t_tk	*tk_new_token(enum e_type type, char *data);
int		ast_add(t_tk **root, t_tk *new_token);
int		ast_add_top(t_tk **root, t_tk *new_token);
int		ast_add_left(t_tk **root, t_tk *new_token);
int		ast_add_right(t_tk **root, t_tk *new_token);
int		ast_add_rd(t_tk **root, t_tk *new_token);
int		tk_is_rd(enum e_type type);

int		ft_is(char c, char const *set);
char	**ft_split(char const *s, char *set);

#endif /* AST_H */
