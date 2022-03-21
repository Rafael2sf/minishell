#ifndef AST_H
# define AST_H

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

// Change return values to int
t_tk	*tk_new(enum e_type type, char *data);
t_tk	*tk_add(t_tk **root, t_tk *new);
t_tk	*tk_add_top(t_tk **root, t_tk *new);
t_tk	*tk_add_rd(t_tk **root, t_tk *new);
int		tk_is_rd(enum e_type type);

#endif /* AST_H */
