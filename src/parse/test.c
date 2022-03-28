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

static int	ms_expand_var(char *var, char *dest);
static int	ms_expand_len(char *s, bool rmv_quote, bool *req_expand);
static int	ms_get_env_len(char *s, int *i);

// Assuming new_s is allocated with len bytes
int ms_expand_str(char *s, int len, bool rmv_quote, char *new_s)
{
	t_pvars	v;
	
	pvars_init(&v);
	printf("len = %d\n", len);
	memset(new_s, '\0', len + 1); // forbbiden
	while (v.end < len)
	{
		ms_parse_quotes(s[v.start], &v);
		if (rmv_quote && ((v.start == 0  
			|| !s[v.start + 1]) && ft_is(s[v.start], "\'\"")))
			(v.start) += 1;
		else if (v.quote == 0 && s[v.start] == '$'
				&& (s[v.start + 1] != ' ' && s[v.start + 1]))
		{
				(v.start) += ms_expand_var(&s[++v.start], &new_s[v.end]);
				while (new_s[v.end])
					(v.end) += 1;
		}
		else
			new_s[v.end++] = s[v.start++];
	}
	return (0);
}

static int	ms_expand_var(char *var, char *dest)
{
	char c;
	int tmp;

	tmp = 0;
	if (*var == '\'' || *var == '\"')
	{
		if (*var == '\"')
			*dest++ = '$';
		while (var[++tmp] && !ft_is(var[tmp], "\'\" "))
			*dest++ = var[tmp];
		return (tmp + 1);
	}
	while (var[tmp] && !ft_is(var[tmp], "\'\"$ "))
		tmp++;
	c = var[tmp];
	var[tmp] = '\0';
	if (getenv(var)) // Protect agaisnt NULL
		strcpy(dest, getenv(var)); // Forbbiden
	var[tmp] = c;
	return (tmp);
}

static int	ms_expand_len(char *s, bool rmv_quote, bool *req_expand) // v.end is used as size
{
	t_pvars	v;
	
	pvars_init(&v);
	if (v.start == 0 && rmv_quote && ft_is(s[v.start], "\'\""))
	{
		(v.end) -= 2;
		(*req_expand) = true;
	}
	while (s[v.start])
	{
		ms_parse_quotes(s[v.start], &v);
		if (v.quote == 0 && s[v.start] == '$' && (s[v.start + 1] != ' ' && s[v.start + 1]))
		{
			(v.end) += ms_get_env_len(s, &v.start);
			(*req_expand) = true;
		}
		else
		{
			(v.start) += 1;
			(v.end) += 1;
		}
	}
	return (v.end);
}

static int	ms_get_env_len(char *s, int *i)
{
	char	*tmp;
	int		size;
	char	c;

	size = 0;
	(*i) += 1;
	tmp = &s[*i];
	if (ft_is(s[*i], "\"\'"))
	{
		if (s[*i] == '\"')
			size += 1;
		while (s[++(*i)] && !ft_is(s[*i], "\'\" "))
			size += 1;
		(*i) += 1;
		return (size);
	}
	while (s[*i] && !ft_is(s[*i], "\'\"$ "))
		(*i) += 1;
	c = s[*i];
	s[*i] = '\0';
	tmp = getenv(tmp);
	s[*i] = c;
	if (!tmp) // strlen handle null
		return (0);
	return (strlen(tmp)); // Using forbbiden
}

# define LEN 8
# define RQ	1

int		main(void)
{
	char	str[200];
	char	buf[200];
	int		len;
	bool	req;

	memcpy(str, "\"'$a$b'\"", LEN);
	str[LEN] = 0;
	printf("str = %s\n", str);
	len = ms_expand_len(str, RQ, &req);
	printf("(req: %d)\n", req);
	if (req)
	{
		ms_expand_str(str, len, RQ, buf);
		printf("buf = %s\n", buf);
	}
	else
		printf("buf = %s\n", str);
	return (0);
}
