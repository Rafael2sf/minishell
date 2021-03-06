/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:34:03 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 17:23:18 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*(haystack + i) && i < len)
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j))
		{
			if ((i + j) >= len)
				break ;
			if (*(needle + j + 1) == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
