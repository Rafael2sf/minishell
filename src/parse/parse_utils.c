/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:12:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/22 17:04:21 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
int	ft_is(char c, char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str++ == c)
			return (1);
	}
	if (*str == c)
		return (1);
	return (0);
}
*/
