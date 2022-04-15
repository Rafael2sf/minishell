/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/15 16:18:59 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../parser/parser.h"
#include "main.h"

static void	ms_init(t_mshell *shell);

int	main(void)
{
	t_mshell			shell;
	int					ret;
	struct termios		term;
	struct termios		term2;

	if (isatty(STDIN_FILENO) != 1)
		return (errno);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &term2);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	ret = 0;
	ms_init(&shell);
	while (1)
	{
		if (call_sigact('h') == -1)
			return (errno);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (shell.stat == 0)
			(shell.prompt) = readline("\033[32mo\033[39m minishell $ ");
		else
			(shell.prompt) = readline("\033[31mx\033[39m minishell $ ");
		(shell.sig_call) = false;
		if (!shell.prompt)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			ms_exit(&shell);
		}
		ret = ms_lexer(&(shell.tokens), (shell.prompt));
		if (shell.tokens && ret != -1)
			add_history(shell.prompt);
		free(shell.prompt);
		if (shell.tokens && ret != -1)
		{
			ret = ms_parser(&shell);
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			if (ret != -1)
				ms_executor(&shell);
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

static void	ms_init(t_mshell *shell)
{	
	extern char	**environ;
	static char	**env;

	(shell->stat) = S_OK;
	(shell->prompt) = NULL;
	(shell->tokens) = NULL;
	(shell->paths) = NULL;
	(shell->sig_call) = false;
	env = ms_init_env(environ);
	(shell->env) = &env;
	if (!shell->env)
		exit (errno);
}
