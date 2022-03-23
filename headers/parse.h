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

// Variables for parsing
typedef struct s_pvars
{
	int	quote;
	int	dquote;
	int	start;
	int	end;
}	t_pvars;

void	pvars_init(t_pvars *v);
t_tk	*tk_new_token(enum e_type type, char *data);

int		tk_is_rd(enum e_type type);
int		ast_add(t_tk **root, t_tk *new_token);
int		ast_add_top(t_tk **root, t_tk *new_token);
int		ast_add_left(t_tk **root, t_tk *new_token);
int		ast_add_right(t_tk **root, t_tk *new_token);
int		ast_add_rd(t_tk **root, t_tk *new_token); // Do not use added because of file limit
void	ast_iter(t_tk *root, void (*f)(void *));

int		ft_is(char c, char const *set);

int		ms_parse(t_tk **root, const char *line);
int		ms_parse_error(int code, char c);
int		ms_create_token(t_tk **root, enum e_type type, const char *ref, int size);

#endif /* AST_H */
