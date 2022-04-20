/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/20 19:45:30 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../parser/parser.h"
#include "main.h"

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
			(shell.prompt) = readline("\033[32m~\033[39m minishell $ ");
		else
			(shell.prompt) = readline("\033[31m~\033[39m minishell $ ");
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
	(shell->stat) = S_OK;
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

	ret = ms_lexer(&(shell->tokens), (shell->prompt));
	if (shell->tokens && ret != -1)
	{
		add_history(shell->prompt);
		ret = ms_parser(shell);
		attr_setting(term2, shell);
		if (ret != -1)
		{
			ms_executor(shell);
		}
		else
			(shell->stat) = errno;
	}
	else if (ret == -1)
		(shell->stat) = 258;
	else
		(shell->stat) = S_OK;
	attr_setting(term2, shell);
	ast_free(&(shell->tokens));
	(shell->tokens) = NULL;
	free(shell->prompt);
	(shell->prompt) = NULL;
	ret = 0;
}
