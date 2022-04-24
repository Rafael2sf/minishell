/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/24 21:12:00 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"
#include "main.h"
#include "../executor/executor.h"

static void	ms_init(t_mshell *shell, char **envp, struct termios *term,
				struct termios *term2);
static void	ms_actions(t_mshell *shell, struct termios *term2);

int	main(int argc, char **argv, char **envp)
{
	t_mshell			shell;
	struct termios		term;
	struct termios		term2;

	(void)(argc);
	(void)(argv);
	ms_init(&shell, envp, &term, &term2);
	while (1)
	{
		call_sigact(SI_RLINE, &shell);
		attr_setting(&term, &shell);
		if (shell.stat == 0)
			(shell.prompt) = readline("\033[32m~\033[39m baby-sh $ ");
		else
			(shell.prompt) = readline("\033[31m~\033[39m baby-sh $ ");
		call_sigact(SI_IGN, &shell);
		(shell.sig_call) = false;
		if (!shell.prompt)
		{
			attr_setting(&term2, &shell);
			ms_exit(&shell);
		}
		ms_actions(&shell, &term2);
	}
	return (0);
}

static void	ms_init(t_mshell *shell, char **envp, struct termios *term,
	struct termios *term2)
{
	if (isatty(STDIN_FILENO) != 1)
	{
		werror("fatal");
		exit(errno);
	}
	prep_terms(term, term2, shell);
	(shell->stat) = 0;
	(shell->prompt) = NULL;
	(shell->tokens) = NULL;
	(shell->paths) = NULL;
	(shell->sig_call) = false;
	(shell->env) = ms_init_env(envp);
	if (!shell->env)
		exit (errno);
}

static void	ms_actions(t_mshell *shell, struct termios *term2)
{
	int	ret;

	if (shell->prompt && *(shell->prompt))
		add_history(shell->prompt);
	ret = ms_lexer(&(shell->tokens), (shell->prompt));
	if (shell->tokens && ret != -1)
	{
		ret = ms_parser(shell);
		attr_setting(term2, shell);
		if (ret != -1)
			ms_executor(shell);
	}
	else if (ret == -1)
		(shell->stat) = 258;
	else
		(shell->stat) = 0;
	attr_setting(term2, shell);
	ast_free(&(shell->tokens));
	(shell->tokens) = NULL;
	free(shell->prompt);
	(shell->prompt) = NULL;
	ret = 0;
}
