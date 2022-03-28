/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:29:35 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/28 18:06:55 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ms_get_env_len(char *s, int *i) // not using correct indexes
{
	char	*tmp;
	int		size;
	char	c;

	size = 0;
	if (ft_is(s[*i], "\"\'"))
	{
		if (s[*i] == '\"')
			size += 1;
		(*i) += 1;
		while (s[*i] && !ft_is(s[*i], "\'\" "))
			(*i) += 1;
		(*i) += 1;
		return (size);
	}
	while (s[*i] && !ft_is(s[*i], "\'\" "))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = getenv(s);
	s[*i] = c;
	if (!tmp) // Make strlen return 0 if null
		return (0);
	(*i) += 2;
	return (strlen(tmp)); // Using forbbiden
}

static int	ms_expand_len(char *s, int rmv_quote)
{
	int	i;
	int	size;
	int	quote;
	
	i = 0;
	quote = 0;
	size = 0;
	if (s[0] == '\'')
		quote = 1;
	if (rmv_quote == 1 && (s[0] == '\'' || s[0] == '\"'))
	{
		while (s[++i] == ' ')
			;
	}
	while (s[i])
	{
		if (!quote && s[i] == '$' && (s[i + 1] != ' ' && s[i + 1]))
		{
			i += 1;
			size += ms_get_env_len(s, &i);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

int	ms_expand_var(char *var, char *dest)
{
	char c;
	int tmp;
	//char *envar;

	tmp = 0;
	if (*var == '\'' || *var == '\"')
	{
		if (*var == '\"')
			*dest++ = '$';
		while (var[++tmp] != '\'')
			*dest++ = var[tmp];
		return (tmp + 1);
	}
	while (var[tmp] && !ft_is(var[tmp], "\'\" "))
		tmp++;
	c = var[tmp];
	var[tmp] = '\0';
	// dest = getenv(var);
	// while (envar && *envar)
	// 	*dest++ = *envar++;
	strcpy(dest, getenv(var)); // Forbbiden
	var[tmp] = c;
	return (tmp);
}

// Assuming new_s is allocated with len bytes
int ms_expand_str(char **s, int len, bool rmv_quote, char *new_s)
{
	t_pvars	v;
	
	pvars_init(&v);
	// new_s = malloc(sizeof(char) * len + 1);
	// if (!new_s)
	// 	return (-1);
	memset(new_s, '\0', len + 1);
	while (v.end < len)
	{
		ms_parse_quotes((*s)[v.start], &v);
		if (rmv_quote && ((v.start == 0  
			|| !(*s)[v.start + 1]) && ft_is((*s)[v.start], "\'\"")))
			(v.start) += 1;
		else if (v.quote == 0 && (*s)[v.start] == '$'
				&& ((*s)[v.start + 1] != ' ' && (*s)[v.start + 1]))
		{
				(v.start) += ms_expand_var(&(*s)[++v.start], &new_s[v.end]);
				while (new_s[v.end])
					(v.end) += 1;
		}
		else
			new_s[v.end++] = (*s)[v.start++];
	}
	return (0);
}

int		main(void)
{
	char	buf[50];
	memcpy(buf, "$USER", 5);
	buf[5] = 0;
	printf("%d\n", ms_expand_len(buf, 1));
	return (0);
}
