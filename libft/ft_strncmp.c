/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:57:58 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/19 17:21:39 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	x = (unsigned char *)s1;
	y = (unsigned char *)s2;
	i = 0;
	while (n)
	{
		if (x[i] == '\0' && y[i] == '\0')
			break ;
		if (x[i] != y[i])
			return (x[i] - y[i]);
		i++;
		n--;
	}
	return (0);
}
