/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:22:39 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/11 16:44:35 by daalmeid         ###   ########.fr       */
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

void prep_act(struct sigaction *act, char ign_or_not)
{
    ft_memset(act, '\0', sizeof(*act));
    if (ign_or_not == 'i')
    	act->sa_handler = SIG_IGN;
	else
		act->sa_sigaction = handle_signals;
    act->sa_flags = SA_SIGINFO;
    sigemptyset(&act->sa_mask);
}