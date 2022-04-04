/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:28:55 by rafernan          #+#    #+#             */
/*   Updated: 2021/10/28 14:59:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is(char c, char const *set)
{
	char	*tmp;

	tmp = (char *)set;
	while (tmp && *tmp)
	{
		if (c == *tmp)
			return (1);
		tmp++;
	}
	return (0);
}
