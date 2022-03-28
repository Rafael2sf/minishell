/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:41:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 16:43:56 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

static void	ft_rlc_unset_copy(char **ptr, char *existing_var, char ***new_ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ptr[i] != NULL)
	{
		if (ptr[i] == existing_var)
		{
			i++;
			free(existing_var);
			continue ;
		}
		(*new_ptr)[j] = ptr[i];
		i++;
		j++;
	}
	(*new_ptr)[j] = NULL;
}

char	**ft_realloc_unset(char ***ptr, size_t size, char *existing_var)
{
	char	**new_ptr;

	new_ptr = malloc(sizeof(char *) * size);
	if (!new_ptr)
	{
		perror("Error allocating variable");
		return (NULL);
	}
	ft_rlc_unset_copy(*ptr, existing_var, &new_ptr);
	free(*ptr);
	*ptr = new_ptr;
	return (*ptr);
}
