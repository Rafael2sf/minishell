/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:34:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 17:24:26 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*ptr;

	if (!s)
		return ;
	ptr = ((char *)(s));
	while (*ptr)
		ptr++;
	write(fd, s, ptr - s);
}

/*
int	main(void)
{
	char	*s;
	int		fd;

	fd = 1;
	s = "Dario Barroca";
	ft_putstr_fd(s, fd);
	return (0);
}
*/