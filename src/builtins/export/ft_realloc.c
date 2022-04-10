/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:18:24 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/04 17:42:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "../builtins.h"

char	**ft_realloc(char ***ptr, size_t size)
{
	size_t	i;
	char	**new_ptr;

	i = 0;
	new_ptr = malloc(sizeof(char *) * size);
	if (!new_ptr)
	{
		perror("Error allocating variable");
		return (NULL);
	}
	while ((*ptr)[i] && i < (size - 1))
	{
		new_ptr[i] = (*ptr)[i];
		i++;
	}
	free(*ptr);
	*ptr = new_ptr;
	(*ptr)[i] = NULL;
	return (*ptr);
}
