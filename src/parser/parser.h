/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:29:51 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/21 18:28:30 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../headers/minishell.h"

int			ms_heredoc(const char *delimitir, t_mshell *shell);
t_bultinf	ms_find_builtin(const char *s);

int			ms_parse_error(int code, t_mshell *shell);
int			ms_parse_input(t_ast *cur, t_mshell *shell);
int			ms_parse_output(t_ast *cur);
char		**ms_parse_paths(char **env);
char		*ms_parse_cmd(char **cmd, t_ast *prev, t_mshell *shell);

int			tk_set_rd(t_ast *tk, void *p);

#endif /* PRSER_H */
