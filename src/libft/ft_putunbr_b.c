/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:24:36 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/01 23:19:18 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr_b(int fd, size_t n, char base, char frmt)
{
	char	c;

	c = (n % base);
	if (n < (size_t)base && n < 10)
		return (ft_putchar(fd, c + '0'));
	else if (n < (size_t)base && n > 9)
	{
		if (frmt == 0)
			return (ft_putchar(fd, c + 'a' - 10));
		else
			return (ft_putchar(fd, c + 'A' - 10));
	}
	if (c >= 10)
	{
		if (frmt == 0)
			return (ft_putunbr_b(fd, n / base, base, frmt)
				+ ft_putchar(fd, c + 'a' - 10));
		else
			return (ft_putunbr_b(fd, n / base, base, frmt)
				+ ft_putchar(fd, c + 'A' - 10));
	}
	else
		return (ft_putunbr_b(fd, n / base, base, frmt)
			+ ft_putchar(fd, c + '0'));
}
