/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/04 17:07:56 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "executor.h"

void	tk_print(void *tk_ptr)
{
	t_ast	*tk;
	char	**ref;
	int		i;

	i = 0;
	tk = (t_ast *)(tk_ptr);
	if (tk->type == E_CMD)
	{
		ref = (char **)(tk->data);
		while (ref[i])
			printf("%s ", ref[i++]);
	}
	if (tk_is_rd(tk->type))
		printf("%s", (char *)(tk->data));
	printf(" ");
}

void	tk_free(void *tk_ptr)
{
	t_ast	*tk;
	char	**arr;
	int		i;

	i = 0;
	tk = (t_ast *)(tk_ptr);
	if (tk->type == E_CMD)
	{
		arr = (char **)(tk->data);
		while (arr[i])
			free(arr[i++]);
		free(tk->data);
	}
	else if (tk_is_rd(tk->type))
		free(tk->data);
	free(tk);
}

/* Minishell main */
int	main(void)
{
	extern char	**environ;
	t_mshell	shell;
	
	//printf("%d\n", getpid());
	(shell.stat) = 0;
	(shell.tokens) = NULL;
	(shell.env) = environ;
	while (1)
	{
		(shell.prompt) = readline("minishell $ ");
		add_history(shell.prompt);
		if (ms_parse(&(shell.tokens), (shell.prompt)) == 0)
		{
			//ast_iter(shell.tokens, tk_print);
			//printf("\n");
			ast_executor(shell.tokens, &shell.stat, shell.env);
		}
		free(shell.prompt);
		ast_iter(shell.tokens, tk_free);
		(shell.tokens) = NULL;
		(shell.prompt) = NULL;
		rl_on_new_line();
	}
	clear_history();
	return (0);
}

/* TEST main 

int	main(void)
{
	char	x[] = "echo > out > out1";
	t_mshell	shell;
	
	(shell.stat) = 0;
	(shell.tokens) = NULL;
	(shell.prompt) = x;
	if (ms_parse(&(shell.tokens), (shell.prompt)) == 0)
	{
		ast_iter(shell.tokens, tk_print);
		ast_executor(shell.tokens, &shell.stat, shell.env);
	}
	ast_iter(shell.tokens, tk_free);
	(shell.tokens) = NULL;
}
*/
/*
int	main(int argc, char **argv)
{
	t_ast	*tokens;
	char	*line;
	
	if (argc == 2)
	{
		line = argv[1];
		if (ms_parse(&tokens, line) == 0)
			ast_iter(tokens, tk_print);
		printf("\n");
		ast_iter(tokens, tk_free);
		line = NULL;
		tokens = NULL;
	}
}
*/
