/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:52:23 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 16:26:25 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_cd(char **input, int fd, char ***env);
int		ft_unset(char **input, int fd, char ***env);
int		ft_export(char **input, int fd, char ***env);
int		ft_echo(char **input, int fd);
int		ft_env(char **input, int fd, char **env);
int		ft_exit(char **input, int fd, char **env, int stat);
int		ft_pwd(char **input, int fd, char **env);

void	ptr_ptr_free(void **ptr);
int		get_total(char **env);
char	**creat_copy(char **env);
char	**sort_env_cpy(char **env_cpy, int total);
char	**altered_split(char const *s, char c);
char	**ft_realloc(char ***ptr, size_t size);
char	**prep_output(char *input, char **env, int name_variable_index);
int		parsing_input_name_unset(char **input);
char	**ft_realloc_unset(char ***ptr, size_t size, char *existing_var);
int		parsing_input_name_export(char *input);

#endif
