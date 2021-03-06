/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:45:17 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/05 15:26:10 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		word_count(const char *s, char c);
static int		get_next_word(const char *s, char c);
static char		**fill_splits(char **ptr_split, int k, char const *s, char c);

char	**ms_split(char const *s, char c)
{
	char	**ptr_split;
	int		k;

	if (s == 0)
		return (NULL);
	k = (word_count(s, c));
	ptr_split = malloc(sizeof(char *) * (k + 1));
	if (!ptr_split)
		return (NULL);
	ptr_split[k] = NULL;
	ptr_split = fill_splits(ptr_split, k, s, c);
	if (!ptr_split)
		return (NULL);
	return (ptr_split);
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	nb_words;
	int	quotes;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == 9)
			i++;
		if (s[i] == '\0')
			break ;
		quotes = 0;
		while (((s[i] != c && s[i] != 9) || quotes != 0) && s[i] != '\0')
		{
			if ((s[i] == '\'' || s[i] == '\"') && quotes == 0)
				quotes = s[i];
			else if (s[i] == quotes)
				quotes = 0;
			i++;
		}
		nb_words++;
	}
	return (nb_words);
}

static int	get_next_word(const char *s, char c)
{
	int	i;
	int	quotes;

	i = 0;
	while (s)
	{
		while (*s == c || *s == 9)
			s++;
		if (*s == '\0')
			return (0);
		quotes = 0;
		while (((s[i] != c && s[i] != 9) || quotes != 0) && s[i] != '\0')
		{
			if ((s[i] == '\'' || s[i] == '\"') && quotes == 0)
				quotes = s[i];
			else if (s[i] == quotes)
				quotes = 0;
			i++;
		}
		return (i);
	}
	return (0);
}

static char	**fill_splits(char **ptr_split, int k, char const *s, char c)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	while (i < k)
	{
		j = 0;
		ptr_split[i] = malloc(sizeof(char) * (get_next_word(s, c) + 1));
		if (!ptr_split[i])
			return (NULL);
		while (*s == c || *s == 9)
			s++;
		quotes = 0;
		while (((*s != c && *s != 9) || quotes != 0) && *s != '\0')
		{
			if ((*s == '\'' || *s == '\"') && quotes == 0)
				quotes = *s;
			else if (*s == quotes)
				quotes = 0;
			ptr_split[i][j++] = *s++;
		}
		ptr_split[i++][j] = '\0';
	}
	return (ptr_split);
}
