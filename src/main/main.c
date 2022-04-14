/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/14 12:52:44 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../parser/parser.h"
#include "main.h"

static void	ms_init(t_mshell *shell);

/* Minishell main */
int	main(void)
{
	t_mshell	shell;
	int			ret;
	struct sigaction	act;
    struct termios		term;
    struct termios		term2;

    prep_act(&act, 'h');
   
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
 		if (sigaction(SIGQUIT, &act, NULL) == -1 ||
        sigaction(SIGINT, &act, NULL) == -1)
    	{
        	perror("Error in sigaction");
     		return (errno);
    	}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (shell.stat == 0)
			(shell.prompt) = readline("\033[32mo\033[39m minishell $ ");
		else
			(shell.prompt) = readline("\033[31mx\033[39m minishell $ ");
		if (shell.sig_call == true)
			(shell.sig_call) = false;
		if (!shell.prompt)
			ms_exit(&shell);
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
	ptr_ptr_free((void **)(*shell.env));
	return (ret);
}

static void	ms_init(t_mshell *shell)
{
	extern 	char	**environ;

	(shell->stat) = S_OK;
	(shell->prompt) = NULL;
	(shell->tokens) = NULL;
	(shell->paths) = NULL;
	(shell->sig_call) = false;
	environ = ms_init_env(environ);
	(shell->env) = &environ;
	if (!shell->env)
		exit (errno);
}
