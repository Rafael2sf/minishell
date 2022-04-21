/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:42:20 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/21 17:24:09 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*ptr;

	if (!s)
		return ;
	ptr = ((char *)(s));
	while (*ptr)
		ptr++;
	write(fd, s, ptr - s);
	ft_putchar_fd('\n', fd);
}

/*
int	main(void)
{
	char	*s;
	int		fd;

	fd = 1;
	s = "Dario Barroca";
	ft_putendl_fd(s, fd);
	return (0);
}
*/
