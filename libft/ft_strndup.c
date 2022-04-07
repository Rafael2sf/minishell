/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:31:48 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/06 11:32:20 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	char	*str;

	if (s)
	{
		str = (char *)malloc(sizeof(char) * (size + 1));
		if (!str)
			return (NULL);
		ft_memcpy(str, s, size);
		*(str + size) = '\0';
		return (str);
	}
	return (NULL);
}
