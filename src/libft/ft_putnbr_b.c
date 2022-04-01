/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:39:25 by rafernan          #+#    #+#             */
/*   Updated: 2021/12/03 12:05:40 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_b(int fd, ssize_t n, char base, char frmt)
{
	int	bytes;

	bytes = 0;
	if (n == LONG_MIN)
	{
		bytes += write(1, "-", 1);
		return (ft_putunbr_b(fd, 0x8000000000000000, base, frmt) + bytes);
	}
	if (n < 0)
	{
		bytes += write(1, "-", 1);
		n = (-n);
	}
	return (ft_putunbr_b(fd, n, base, frmt) + bytes);
}
