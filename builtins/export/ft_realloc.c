/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:18:24 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/28 14:14:18 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/libft.h"
#include "ft_export.h"

char	**ft_realloc(char ***ptr, size_t size)
{
	int		i;
	char	**new_ptr;

	i = 0;
	new_ptr = malloc(sizeof(char *) * size);
	if (!new_ptr)
	{
		perror("Error allocating variable");
		return (NULL);
	}
	while ((*ptr)[i])
	{
		new_ptr[i] = (*ptr)[i];
		i++;
	}
	free(*ptr);
	*ptr = new_ptr;
	(*ptr)[i] = NULL;
	return (*ptr);
}
