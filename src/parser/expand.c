/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:50 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/14 14:21:45 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../lexer/lexer.h"
#include "parser.h"

static void	ms_expand_str(char *s, char *b, int stat);
static char	*ms_get_env(char *s, char *b, int stat, t_pvars *v);
static int	ms_expand_len(char *s, bool *req_expand, int stat);
static int	ms_get_env_len(char *s, int *i, int stat);

int	nbr_len(int n)
{
	int		i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ms_expand(char *str, void *stat)
{
	char	*buf;
	int		len;
	bool	req_expand;

	req_expand = false;
	len = ms_expand_len(str, &req_expand, *(int *)stat);
	if (req_expand)
	{
		buf = malloc(sizeof(char) * (len + 1));
		if (!buf)
			return (NULL);
		buf[len] = '\0';
		ms_expand_str(str, buf, *(int *)stat);
		return (buf);
	}
	return (str);
}

static void	ms_expand_str(char *s, char *buf, int stat)
{
	t_pvars	v;

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
				ms_get_env(s, buf, stat, &v);
			else if (v.dquote)
				buf[v.end++] = s[v.start];
		}
		else
			buf[v.end++] = s[v.start];
		(v.start) += 1;
	}
}

static char	*ms_get_env(char *s, char *buff, int stat, t_pvars *v)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(v->start) += 1;
	ptr = &s[v->start];
	if (s[v->start] == '?')
	{
		tmp = ft_itoa(stat); // Not freeing tmp
		while (tmp && *tmp)
			buff[v->end++] = *tmp++;
		if (!tmp)
			perror("minishell");
		//else
			//free(tmp);
	}
	while (s[v->start] && !ft_is(s[v->start], "\'\"/$ \t\n"))
		(v->start) += 1;
	c = s[v->start];
	s[v->start] = '\0';
	tmp = getenv(ptr);
	s[v->start] = c;
	(v->start) -= 1;
	while (tmp && *tmp)
			buff[v->end++] = *tmp++;
	return (tmp);
}

static int	ms_expand_len(char *s, bool *req_expand, int stat)
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
				(v.end) += ms_get_env_len(s, &v.start, stat);
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

static int	ms_get_env_len(char *s, int *i, int stat)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(*i) += 1;
	ptr = &s[*i];
	if (s[*i] == '?')
		return (nbr_len(stat));
	while (s[*i] && !ft_is(s[*i], "\'\"/$ \t\n"))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = getenv(ptr);
	s[*i] = c;
	(*i) -= 1;
	return (ft_strlen(tmp));
}
