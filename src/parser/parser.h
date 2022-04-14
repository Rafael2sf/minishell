/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:29:51 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/13 15:46:22 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char		*ms_expand(char *str);
int			ms_heredoc(const char *delimitir, t_mshell *shell);
t_bultinf	ms_find_builtin(const char *s);

int			ms_parse_error(int code);
int			ms_parse_input(t_ast *cur, t_mshell *shell);
int			ms_parse_output(t_ast *cur);
char		**ms_parse_paths(void);
char		*ms_parse_cmd(char **cmd, char **paths);

#endif /* PRSER_H */
