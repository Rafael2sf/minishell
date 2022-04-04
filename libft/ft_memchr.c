/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:24:06 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 16:32:49 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	if (s)
	{
		tmp = (unsigned char *)(s);
		while (i < n)
		{
			if (*(tmp + i) == (unsigned char)(c))
				return ((void *)(tmp + i));
			i++;
		}
	}
	return (NULL);
}
