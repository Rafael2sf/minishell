/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:52:12 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/31 11:13:09 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

int	ft_strlen_m(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

int	ft_free_m(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

int	ft_memcpy_m(char **d, char **s)
{
	int	i;

	if (!d || !s)
		return (-1);
	i = -1;
	while (s[++i])
		d[i] = s[i];
	return (i);
}

char	**ft_strjoin_m(char **a, char **b)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	len = ft_strlen_m(a);
	len += ft_strlen_m(b);
	new = malloc(sizeof(char *) * len + 1);
	i = 0;
	j = 0;
	while (a[i])
		new[i++] = a[j++];
	j = 0;
	while (b[j])
		new[i++] = b[j++];
	new[i] = NULL;
	free(a);
	free(b);
	return (new);
}
