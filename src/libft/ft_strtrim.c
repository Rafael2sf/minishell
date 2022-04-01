/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:30:26 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/01 23:02:18 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	x;
	size_t	y;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	x = 0;
	y = ft_strlen(s1);
	while (s1[x] && ft_is(s1[x], set))
		x++;
	while (y > x && ft_is(s1[y - 1], set))
		y--;
	str = (char *)malloc(sizeof(char) * (y - x + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (x < y)
		str[i++] = s1[x++];
	str[i] = '\0';
	return (str);
}
