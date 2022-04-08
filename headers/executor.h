/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:21:45 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/08 15:24:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		ms_get_input(t_ast *cur);
int		ms_get_output(t_ast *cur);
char	**ms_paths(void);
char	*ms_newcmd(char **cmd, char **paths);
int		ms_heredoc(const char *delimitir);

# endif
