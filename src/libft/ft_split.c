/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:35:41 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/30 14:52:07 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_size(char const *s, char *set)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	str = (char *)(s);
	while (*(str + i) && ft_is(str[i], set))
		i++;
	if (!*(str + i))
		return (0);
	j++;
	while (*(str + i))
	{
		if (ft_is(str[i], set) && *(str + i + 1)
			&& !ft_is(str[i + 1], set))
			j++;
		i++;
	}
	return (j);
}

static char	**ft_split_helper(char **p, char const *s, char *set, size_t size)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	str = (char *)(s);
	while (*str && j < size)
	{
		while (*str && ft_is(*str, set))
			str++;
		i = 0;
		while (*(str + i) && !ft_is(str[i], set))
			i++;
		p[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!p[j])
			return (NULL);
		ft_strlcpy(p[j], str, i + 1);
		j++;
		str = (str + i);
	}
	p[j] = NULL;
	return (p);
}
#include <stdio.h>
char	**ft_split(char const *s, char *set)
{
	char	**tmp;
	size_t	size;

	if (!s || !*s)
		return (NULL);
	size = ft_split_size(s, set);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (NULL);
	ft_split_helper(tmp, s, set, size);
	return (tmp);
}

int	main(void)
{
	char	s[] = "\t    \t   hi   \t   \"def\"\n";
	char	**a = ft_split(s, "\t ");

	int		i = 0;
	while (a[i])
		printf("%s", a[i++]);
}
