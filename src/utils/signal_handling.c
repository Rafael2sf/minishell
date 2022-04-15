/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:22:39 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/15 16:29:25 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_signals_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		clear_history();
		write(STDOUT_FILENO, "\n", 1);
		exit(1);
	}
}

static void	prep_act(struct sigaction *act, char ign_or_not)
{
	ft_memset(act, '\0', sizeof(*act));
	if (ign_or_not == 'i')
		act->sa_handler = SIG_IGN;
	else if (ign_or_not == '<')
		act->sa_sigaction = handle_signals_heredoc;
	else if (ign_or_not == 'h')
		act->sa_sigaction = handle_signals;
	else if (ign_or_not == 'd')
		act->sa_handler = SIG_DFL;
	act->sa_flags = SA_SIGINFO;
	sigemptyset(&act->sa_mask);
}

int	call_sigact(char act_choice)
{
	struct sigaction	act;

	prep_act(&act, act_choice);
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		perror("Error in sigaction");
		return (-1);
	}
	return (0);
}
