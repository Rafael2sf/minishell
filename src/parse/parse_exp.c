/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:50 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 11:10:45 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ms_expand_str(char *s, char *b);
static char	*ms_get_env(char *s, int *i);
static int	ms_expand_len(char *s, bool *req_expand);
static int	ms_get_env_len(char *s, int *i);

/*															 READ --> MUST DO $? */

char	*ms_expand(char *str)
{
	char	*buf;
	int		len;
	bool	req_expand;

	req_expand = false;
	len = ms_expand_len(str, &req_expand);
	if (req_expand)
	{
		buf = malloc(sizeof(char) * (len + 1));
		if (!buf)
			return (NULL);
		buf[len] = '\0';
		ms_expand_str(str, buf);
		return (buf);
	}
	return (str);
}

static void	ms_expand_str(char *s, char *buf)
{
	t_pvars	v;
	char	*envar;

	pvars_init(&v);
	while (s[v.start])
	{
		ms_parse_quotes(s[v.start], &v);
		if ((!v.quote && s[v.start] == '\"')
			|| (!v.dquote && s[v.start] == '\''))
			;
		else if (!v.quote && s[v.start] == '$')
		{
			if (s[v.start + 1] != '\"' && s[v.start + 1])
			{
				envar = ms_get_env(s, &v.start);
				while (envar && *envar)
					buf[v.end++] = *envar++;
			}
			else if (v.dquote)
				buf[v.end++] = s[v.start];
		}
		else
			buf[v.end++] = s[v.start];
		(v.start) += 1;
	}
}

static char	*ms_get_env(char *s, int *i)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(*i) += 1;
	ptr = &s[*i];
	while (s[*i] && !ft_is(s[*i], "\'\"/$ \t"))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = getenv(ptr);
	s[*i] = c;
	(*i) -= 1;
	return (tmp);
}

static int	ms_expand_len(char *s, bool *req_expand)
{
	t_pvars	v;

	pvars_init(&v);
	while (s[v.start])
	{
		ms_parse_quotes(s[v.start], &v);
		if ((!v.quote && s[v.start] == '\"')
			|| (!v.dquote && s[v.start] == '\''))
			(*req_expand) = true;
		else if (!v.quote && s[v.start] == '$')
		{
			if (s[v.start + 1] != '\"' && s[v.start + 1])
			{
				(*req_expand) = true;
				(v.end) += ms_get_env_len(s, &v.start);
			}
			else if (v.dquote)
				(v.end) += 1;
		}
		else
			(v.end) += 1;
		(v.start) += 1;
	}
	return (v.end);
}

static int	ms_get_env_len(char *s, int *i)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(*i) += 1;
	ptr = &s[*i];
	while (s[*i] && !ft_is(s[*i], "\'\"/$ \t"))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = getenv(ptr);
	s[*i] = c;
	(*i) -= 1;
	return (ft_strlen(tmp));
}
