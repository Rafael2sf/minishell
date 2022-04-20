/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/19 17:49:31 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../parser/parser.h"
#include "main.h"

static void	ms_init(t_mshell *, char **);

int	main(int argc, char **argv, char **envp)
{
	t_mshell			shell;
	int					ret;
	struct termios		term;
	struct termios		term2;

	(void)(argc);
	(void)(argv);
	if (isatty(STDIN_FILENO) != 1)
		return (errno);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &term2);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	ret = 0;
	ms_init(&shell, envp);
	while (1)
	{
		if (call_sigact('h') == -1)
			return (errno);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (shell.stat == 0)
			(shell.prompt) = readline("\033[32m~\033[39m minishell $ ");
		else
			(shell.prompt) = readline("\033[31m~\033[39m minishell $ ");
		if (call_sigact('i') == -1)
			return (errno);
		(shell.sig_call) = false;
		if (!shell.prompt)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			ms_exit(&shell);
		}
		if (shell.prompt && (*shell.prompt))
			add_history(shell.prompt);
		ret = ms_lexer(&(shell.tokens), (shell.prompt));
		free(shell.prompt);
		(shell.prompt) = NULL;
		if (shell.tokens && ret != -1)
		{
			ret = ms_parser(&shell);
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			if (ret != -1)
				ms_executor(&shell);
			else
				(shell.stat) = 1;
		}
		else if (ret == -1)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			(shell.stat) = 258;
		}
		else
			(shell.stat) = S_OK;
		ast_free(&(shell.tokens));
		(shell.tokens) = NULL;
		(shell.prompt) = NULL;
		ret = 0;
	}
	return (ret);
}

static void	ms_init(t_mshell *shell, char **envp)
{
	(shell->stat) = S_OK;
	(shell->prompt) = NULL;
	(shell->tokens) = NULL;
	(shell->paths) = NULL;
	(shell->sig_call) = false;
	(shell->env) = ms_init_env(envp);
	if (!shell->env)
		exit (errno);
}
