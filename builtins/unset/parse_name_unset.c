/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:38:49 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:40:54 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static char	*trim_quotes(char *split_input)
{
	char	*trimmed_str;

	trimmed_str = NULL;
	if (split_input[0] == '\'')
		trimmed_str = ft_strtrim(split_input, "\'");
	else if (split_input[0] == '\"')
		trimmed_str = ft_strtrim(split_input, "\"");
	if (!trimmed_str)
	{	
		perror("error allocating memory in trim_quotes");
		return (NULL);
	}
	else
	{
		free(split_input);
		split_input = trimmed_str;
	}
	return (split_input);
}

static int	check_first_c(char *split_input, int *error_count)
{
	if (ft_isdigit(split_input[0]) && *error_count == 0)
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(split_input, 2);
		ft_putendl_fd(": invalid parameter name", 2);
		(*error_count)++;
		return (0);
	}
	return (1);
}

int	parsing_input_name_unset(char **split_input, int *error_count)
{
	int		i;
	char	*name;

	i = 0;
	if ((*split_input)[0] == '\'' || (*split_input)[0] == '\"')
		*split_input = trim_quotes(*split_input);
	if (*split_input == NULL)
		return (0);
	if (check_first_c(*split_input, error_count) == 0)
		return (0);
	while ((*split_input)[i] != '\0')
	{
		if (!ft_isalnum((*split_input)[i]) && (*split_input)[i] != '_'
			&& *error_count == 0)
		{	
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd((*split_input), 2);
			ft_putendl_fd(": invalid parameter name", 2);
			(*error_count)++;
			return (0);
		}
		i++;
	}
	return (i);
}
