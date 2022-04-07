/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:32:13 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 10:58:12 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	tk_print(void *tk_ptr, int depth);
static void	tk_print_cmd(char **data);
static void	tk_print_rd(char *data, t_type type);


void	ast_print(t_ast *root, int depth)
{
	if (!root)
		return ;
	ast_print(root->left, depth + 1);
	tk_print(root, depth);
	ast_print(root->right, depth + 1);
}

/*
	Write a node data
*/
static void	tk_print(void *tk_ptr, int depth)
{
	t_ast		*tk;
	
	while (depth--)
		ft_putstr(STDERR_FILENO, "  ");
	tk = (t_ast *)(tk_ptr);
	if (tk->type == E_CMD)
		tk_print_cmd((char **)(tk->data));
	else if (tk->type == E_PIPE)
		ft_putstr(STDERR_FILENO,"(P)");
	else
		tk_print_rd((char *)(tk->data), tk->type);
	ft_putchar(STDERR_FILENO, '\n');
}

static void	tk_print_cmd(char **data)
{
	char	**ref;
	int		i;

	i = 0;
	ref = data;
	ft_putchar(STDERR_FILENO, '(');
	while (ref[i])
	{
		ft_putstr(STDERR_FILENO, ref[i++]);
		ft_putchar(STDERR_FILENO, ':');
	}
	ft_putchar(STDERR_FILENO, ')');
}

static void	tk_print_rd(char *data, t_type type)
{
	ft_putchar(STDERR_FILENO, '[');
	if (type == E_LSR)
		ft_putchar(STDERR_FILENO, '<');
	else if (type == E_LLSR)
		ft_putstr(STDERR_FILENO, "<<");
	else if (type == E_GRT)
		ft_putchar(STDERR_FILENO, '>');
	else if (type == E_GGRT)
		ft_putstr(STDERR_FILENO, ">>");
	ft_putstr(STDERR_FILENO, "]{");
	ft_putstr(STDERR_FILENO, data);
	ft_putchar(STDERR_FILENO, '}');
}
