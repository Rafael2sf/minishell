/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:52:23 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/10 17:36:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../headers/minishell.h"

int		get_total(char **env);
char	**sort_env_cpy(char **env_cpy, int total);
char	**ft_realloc(char ***ptr, size_t size);
char	**prep_output(char *input, char **env, int name_variable_index);
int		parsing_input_name_unset(char **input);
char	**ft_realloc_unset(char ***ptr, size_t size, char *existing_var);
int		parsing_input_name_export(char *input);

#endif /* BUILTINS_H */
