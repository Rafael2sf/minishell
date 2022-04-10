/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:52:37 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/10 17:35:59 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

void	pvars_init(t_pvars *v);
int		tk_is_rd(t_type type);
void	ms_parse_quotes(char c, t_pvars *v);
t_ast	*tk_new_token(t_type type, void *ref);

int		ms_create_token(t_ast **root, t_type type, char *s, int size);
int		ms_parse_token(t_ast **root, char *line, t_pvars *v);
int		ms_lexer_error(int code, char c, bool use_perror);

int		ast_add(t_ast **root, t_ast *new_token);
int		ast_add_top(t_ast **root, t_ast *new_token);
int		ast_add_left(t_ast **root, t_ast *new_token);
int		ast_add_right(t_ast **root, t_ast *new_token);

#endif /* LEXER_H */
