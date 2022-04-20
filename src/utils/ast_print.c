/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:32:13 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 16:47:52 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	tk_print(t_ast *tk, int depth, int cmd_only);
static void	tk_print_cmd(void *data);
static void	tk_print_rd(char *data, t_type type);

void	ast_print(t_ast *root, int depth, int cmd_only)
{
	if (!root)
		return ;
	ast_print(root->left, depth + 1, cmd_only);
	tk_print(root, depth, cmd_only);
	ast_print(root->right, depth + 1, cmd_only);
}

/*
	Write a node data
*/
static void	tk_print(t_ast *tk, int depth, int cmd_only)
{
	if (!tk)
		return ;
	while (!cmd_only && depth--)
		ft_putstr(STDERR_FILENO, "---");
	if (!cmd_only)
		ft_putnbr(STDERR_FILENO, (int)tk->type);
	if (tk->type == E_CMD || tk->type == E_UNDEF)
		tk_print_cmd((tk->data));
	else if (tk->type == E_PIPE && !cmd_only)
		ft_putstr(STDERR_FILENO, "(P)");
	else if (!cmd_only)
		tk_print_rd((char *)(tk->data), tk->type);
	if (cmd_only && (tk->type == E_CMD || tk->type == E_UNDEF))
	{
		ft_putchar(STDERR_FILENO, ' ');
		ft_putnbr(STDERR_FILENO, tk->p[0]);
		ft_putchar(STDERR_FILENO, ' ');
		ft_putnbr(STDERR_FILENO, tk->p[1]);
		ft_putchar(STDERR_FILENO, '\n');
	}
	else if (!cmd_only)
		ft_putchar(STDERR_FILENO, '\n');
}

static void	tk_print_cmd(void *data)
{
	char	**ref;
	int		i;

	i = 0;
	ref = (char **)data;
	ft_putchar(STDERR_FILENO, '(');
	while (ref && ref[i])
	{
		ft_putstr(STDERR_FILENO, ref[i++]);
		if (ref[i])
			ft_putchar(STDERR_FILENO, ':');
	}
	ft_putstr(STDERR_FILENO, ")");
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
	ft_putstr(STDERR_FILENO, "](");
	if (type != E_UNDEF)
		ft_putstr(STDERR_FILENO, data);
	ft_putchar(STDERR_FILENO, ')');
}
