/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:40:54 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/20 10:39:59 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if ((size < start) || len == 0)
		return (ft_strdup(""));
	if (len > (size - start))
		len = (size - start);
	buffer = (char *)ft_calloc(sizeof(char), len + 1);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, (s + start), len + 1);
	return (buffer);
}
