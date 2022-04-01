/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:54:25 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/19 14:23:07 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	char	*s;
	char	*d;
	size_t	tmp;

	if (dst && src)
	{
		tmp = siz;
		d = (char *)(dst);
		while (tmp-- && *d)
			d++;
		tmp = siz - (d - dst);
		s = (char *)(src);
		if (tmp == 0)
			return ((d - dst) + ft_strlen(s));
		tmp = (d - dst);
		while (*s)
		{
			if ((siz - (d - dst)) > 1)
				*d++ = *s;
			s++;
		}
		*d = '\0';
		return (tmp + (s - src));
	}
	return (siz);
}
