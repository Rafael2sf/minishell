/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:03:00 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/22 18:19:23 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parse.h"
#include "../../headers/minishell.h"

static int	ms_parse_token(t_tk **root, const char *line, int *i, int *j);
static int	ms_token_pipe(t_tk **root, const char *line, int *i, int *j);
static int	ms_token_rd(t_tk **root, const char *line, int *i, int *j);

int	ms_parse(t_tk **root, const char *line)
{
	int	i;
	int	j;
	int	quote;
	int	dquote;
	
	i = 0;
	j = 0;
	dquote = 0;
	quote = 0;
	while (*line && *line == ' ')
		line++;
	while (1)
	{
		if (line[j] == '\0')
		{
			while (--j >= i && line[j] == ' ')
				;
			write(1, &line[i], j - i + 1);
			break ;
		}
		if (ft_is(line[j], ">|<"))
		{
			ms_parse_token(root, line, &i, &j);
			i = j;
		}
		else
			j++;
	}
	return (0);
}

static int	ms_parse_token(t_tk **root, const char *line, int *i, int *j)
{
	int	tmp;
	int	ret;
	
	tmp = (*j) - 1;
	// Remove spaces before
	while (tmp > *i && line[tmp] == ' ')
		tmp--;
	// get previous word
	if (tmp - *i >= 0)
		write(1, &line[*i], tmp - *i + 1); // Set word if exists
	
	// Handle case
	if (line[*j] == '|')
		ret = ms_token_pipe(root, line, i, j);
	else
		ret = ms_token_rd(root, line, i, j);

	// Skip spaces
	while (line[*j] && line[*j] == ' ')
		(*j)++;
	return  (ret);
}

static int	ms_token_pipe(t_tk **root, const char *line, int *i, int *j)
{
	write(1, &line[*j], 1); // Set pipe
	(*j)++;
	return (0);
}

static int	ms_token_rd(t_tk **root, const char *line, int *i, int *j)
{
	write(1, &line[*j], 1); // Set type
	(*j) += 1;
	if (ft_is(line[*j], "<>"))
	{
			write(1, &line[*j], 1); // Set type again ?
			(*j) += 1;
	}
	while (line[*j] && line[*j] == ' ')
		(*j)++;
	(*i) = (*j);
	while (line[*j] && line[*j] != ' ')
		(*j)++;
	write(1, &line[*i], *j - *i); // Create word
	return (0);
}

static void	ms_set_quotes(char c, int *quotes, int *dquotes)
{
}

/* TETS */
int	main(void)
{
	ms_parse(NULL, "   a   ");
}

/*

" "++
while (1)
{
	if (special)
	{
		>
	}
	else
		++:
}


*/