/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:23:39 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 21:34:56 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*res;

	res = NULL;
	if (s)
	{
		tmp = (char *)s;
		if (*tmp == (char)c)
			res = tmp;
		while (*tmp++)
		{
			if (*tmp == (char)c)
				res = tmp;
		}
	}
	return (res);
}
