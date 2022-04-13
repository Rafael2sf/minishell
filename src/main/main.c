/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:58:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/12 16:55:18 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "main.h"

static int	ms_valid_exit(t_ast *tokens);
static void	ms_exit(t_mshell *shell);
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
		// ☕
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (shell.stat == 0)
			(shell.prompt) = readline("\033[32m-\033[39m baby~sh ☕ ");
		else
			(shell.prompt) = readline("\033[31m-\033[39m baby~sh ☕ ");
		add_history(shell.prompt);
		if (!shell.prompt)
			ms_exit(&shell);
		ret = ms_lexer(&(shell.tokens), (shell.prompt));
		free(shell.prompt);
		if (shell.tokens && ret != -1)
		{
			ret = ms_parser(shell.tokens);
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			if (ms_valid_exit(shell.tokens))
				ms_exit(&shell);
			else if (ret != -1)
				ms_executor(&shell);
			else
				(shell.stat) = 1;
		}
		else
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term2);
			(shell.stat) = 258;
		}	
		ast_free(&(shell.tokens));
		(shell.tokens) = NULL;
		(shell.prompt) = NULL;
		ret = 0;
		printf("stat = %d\n", (shell.stat));
	}
	return (ret);
}

static int	ms_valid_exit(t_ast *tokens)
{
	char		**data;

	data = (char **)(tokens->data);
	return (tokens->type == E_CMD && data && ft_strncmp(data[0], "exit", 5) == 0
			&& (!data[1] || (data[1] && !data[2])));
}

static void	ms_exit(t_mshell *shell)
{
	char		*cmd[3];
	int			val;
	char		**data;

	data = NULL;
	if (shell->tokens)
		data = (char **)(shell->tokens->data);
	cmd[0] = "exit";
	cmd[2] = NULL;
	if (data && data[1])
	{
		val = ft_atoi(data[1]);
		cmd[1] = ft_strdup(data[1]);
	}
	else
	{
		val = (shell->stat);
		cmd[1] = NULL;
	}
	ptr_ptr_free((void **)(*shell->env));
	ast_free(&(shell->tokens));
	ft_exit(cmd, -1, &val, NULL);
}

static void	ms_init(t_mshell *shell)
{
	extern 	char	**environ;

	(shell->stat) = 0;
	(shell->prompt) = NULL;
	(shell->tokens) = NULL;
	environ = ms_init_env(environ);
	(shell->env) = &environ;
	if (!shell->env)
		exit (errno);
}
