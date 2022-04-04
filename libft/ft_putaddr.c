/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:40:45 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/01 23:21:40 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr(int fd, size_t addr)
{
	if (!addr)
		return (write(fd, "0x0", 3));
	return (write(fd, "0x", 2) + ft_putunbr_b(fd, addr, 16, 0));
}
