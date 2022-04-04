/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:42:00 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/26 12:06:05 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr(int fd, const char *s)
{
	char	*ptr;

	if (!s)
		return (write(fd, "(null)", 6));
	ptr = ((char *)(s));
	while (*ptr)
		ptr++;
	write(fd, s, ptr - s);
	return (ptr - s);
}
