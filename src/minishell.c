/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/08 18:32:31 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/executor.h"
#include "../headers/builtins.h"

static char **ms_env_creation(char **envp);

void	rl_replace_line(const char *text, int clear_undo);
/*
static void handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_redisplay();
    }
}

static void prep_act(struct sigaction *act)
{
    ft_memset(act, '\0', sizeof(*act));
    act->sa_sigaction = handle_signals;
    act->sa_flags = SA_SIGINFO;
    sigemptyset(&act->sa_mask);
}
*/
/* Minishell main */
int	main(void)
{
	extern char			**environ;
	t_mshell			shell;
    /*
	struct sigaction	act;
    struct termios		term;
    struct termios		term2;

    prep_act(&act);
    if (sigaction(SIGQUIT, &act, NULL) == -1 ||
        sigaction(SIGINT, &act, NULL) == -1)
    {
        perror("Error in sigaction");
        return (errno);
    }
    if (isatty(STDIN_FILENO) != 1)
        return (errno);
    tcgetattr(STDIN_FILENO, &term);
    tcgetattr(STDIN_FILENO, &term2);
    term.c_cc[VQUIT] = _POSIX_VDISABLE;
	*/
	(shell.stat) = 0;
	(shell.tokens) = NULL;
	environ = ms_env_creation(environ);
	(shell.env) = &environ;
	if (!shell.env)
		return (errno);
	if (DEBUG)
		printf("PID = %d\n", getpid());
	while (1)
	{
		//tcsetattr(STDIN_FILENO, TCSANOW, &term);
		(shell.prompt) = readline("minishell $ ");
		//tcsetattr(STDIN_FILENO, TCSANOW, &term2);
		add_history(shell.prompt);
		if (!shell.prompt)
			break ; // exit
		if (ms_parse(&(shell.tokens), (shell.prompt)) == 0 && shell.tokens)
		{
			free(shell.prompt);
			ast_executor(&shell);
		}
		else
			free(shell.prompt);
		ast_iter_in(shell.tokens, tk_free, 1, NULL);
		(shell.tokens) = NULL;
		(shell.prompt) = NULL;
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
