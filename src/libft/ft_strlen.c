/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:35:02 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/26 12:04:23 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = (char *)(s);
	while (*tmp)
		tmp++;
	return (tmp - s);
}
