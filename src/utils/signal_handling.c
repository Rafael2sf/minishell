/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:22:39 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/14 12:06:32 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

static void handle_signals_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		clear_history();
		write(1, "\n", 1);
		exit(1);
    }
}

void prep_act(struct sigaction *act, char ign_or_not)
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

