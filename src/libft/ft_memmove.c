/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 09:12:45 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 16:33:10 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)(dst);
	s = (char *)(src);
	if (d && s)
	{
		if ((s < d) && (d < (s + len)))
		{
			s += len;
			d += len;
			while (len--)
				*--d = *--s;
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
