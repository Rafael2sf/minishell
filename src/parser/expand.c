/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:50 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/15 17:17:02 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../lexer/lexer.h"
#include "parser.h"

static void	ms_expand_str(char *s, char *buf, t_mshell *shell);
static char	*ms_get_env(char *s, char *buff, t_mshell *shell, t_pvars *v);
static int	ms_expand_len(char *s, bool *req_expand, t_mshell *shell);
static int	ms_get_env_len(char *s, int *i, t_mshell *shell);

char	*ms_expand(char *str, t_mshell *shell)
{
	char	*buf;
	int		len;
	bool	req_expand;

	req_expand = false;
	len = ms_expand_len(str, &req_expand, shell);
	if (req_expand)
	{
		buf = malloc(sizeof(char) * (len + 1));
		if (!buf)
			return (NULL);
		buf[len] = '\0';
		ms_expand_str(str, buf, shell);
		return (buf);
	}
	return (str);
}

static void	ms_expand_str(char *s, char *buf, t_mshell *shell)
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
				ms_get_env(s, buf, shell, &v);
			else if (v.dquote)
				buf[v.end++] = s[v.start];
		}
		else
			buf[v.end++] = s[v.start];
		(v.start) += 1;
	}
}

static char	*ms_get_env(char *s, char *buff, t_mshell *shell, t_pvars *v)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(v->start) += 1;
	ptr = &s[v->start];
	if (s[v->start] == '?')
	{
		tmp = ft_itoa(shell->stat); // Not freeing tmp
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
	tmp = ft_getenv(ptr, shell->env);
	s[v->start] = c;
	(v->start) -= 1;
	while (tmp && *tmp)
			buff[v->end++] = *tmp++;
	return (tmp);
}

static int	ms_expand_len(char *s, bool *req_expand, t_mshell *shell)
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
				(v.end) += ms_get_env_len(s, &v.start, shell);
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

static int	ms_get_env_len(char *s, int *i, t_mshell *shell)
{
	char	*ptr;
	char	*tmp;
	char	c;

	(*i) += 1;
	ptr = &s[*i];
	if (s[*i] == '?')
		return (nbr_len(shell->stat));
	while (s[*i] && !ft_is(s[*i], "\'\"/$ \t\n"))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = ft_getenv(ptr, shell->env);
	s[*i] = c;
	(*i) -= 1;
	return (ft_strlen(tmp));
}
