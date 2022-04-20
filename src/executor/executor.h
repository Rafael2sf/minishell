/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:21:45 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 12:33:42 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../headers/minishell.h"

int	ms_valid_exit(t_ast *tokens);
int	tk_close_all(t_ast *tk, void *p);
int	tk_exec(t_ast *tk, void *p);
int	tk_wait(t_ast *tk, void *p);

#endif /* EXECUTOR_H */
