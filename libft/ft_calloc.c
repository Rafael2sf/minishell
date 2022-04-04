/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:54:41 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 09:37:40 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*buffer;

	buffer = (char *)malloc(count * size);
	if (buffer)
	{
		ft_bzero(buffer, size * count);
		return (buffer);
	}
	return (NULL);
}
