/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:14:30 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 21:24:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;

	if (s)
	{
		tmp = (char *)(s);
		while (*tmp)
		{
			if (*tmp == (char)c)
				return (tmp);
			tmp++;
		}
		if (*tmp == c)
			return (tmp);
	}
	return (NULL);
}
