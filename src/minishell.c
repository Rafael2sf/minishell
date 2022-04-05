/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/05 17:26:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/executor.h"

static char **ms_env_creation(char **envp);

/* Minishell main */
int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;
	
	(void)(argc);
	(void)(argv);
	(shell.stat) = 0;
	(shell.tokens) = NULL;
	(shell.env) = ms_env_creation(envp);
	if (!shell.env)
		return (errno);
	while (1)
	{
		//system(ft_strjoin("lsof -a -p ", ft_itoa(getpid())));
		(shell.prompt) = readline("minishell $ ");
		add_history(shell.prompt);
		if (ms_parse(&(shell.tokens), (shell.prompt)) == 0)
		{
			free(shell.prompt);
			if (DEBUG)
			{
				ast_iter(shell.tokens, tk_print);
				printf("\n");
			}
			ast_executor(shell.tokens, &shell.stat, shell.env);
		}
		else
			free(shell.prompt);
		ast_iter(shell.tokens, tk_free);
		(shell.tokens) = NULL;
		(shell.prompt) = NULL;
		rl_on_new_line();
	}
	clear_history();
	return (0);
}

static char **ms_env_creation(char **envp)
{
	char	**env_cpy;

	env_cpy = creat_copy(envp);
	if (!env_cpy)
	{
		perror("error creating env");
		return (NULL);
	}
	change_shlvl(&env_cpy);
	if (!env_cpy)
		return (NULL);
	env_cpy = export_at_start_process(env_cpy);
	return (env_cpy);
}
