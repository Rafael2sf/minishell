/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:52:23 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:58:18 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

void	ptr_ptr_free(void **ptr);
int		get_total(char **env);
char	**creat_copy(char **env);
char	**sort_env_cpy(char **env_cpy, int total);
char	**ft_export(char *input, int fd, char **env);
char	**altered_split(char const *s, char c);
char	**ft_realloc(char ***ptr, size_t size);
char	**prep_output(char *split_input, char **env, int name_variable_index);
char	**ft_unset(char *input, int fd, char **env);
int		parsing_input_name_unset(char **split_input, int *error_count);
char	**ft_realloc_unset(char ***ptr, size_t size, char *existing_var);
int		parsing_input_name_export(char *split_input, int *error_count);

#endif