/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:38:26 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/20 15:39:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	prep_terms(struct termios *term, struct termios *term2)
{
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, term2);
	term->c_cc[VQUIT] = _POSIX_VDISABLE;
	term->c_lflag &= ~ECHOCTL;
}

void	attr_setting(struct termios *term, t_mshell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0)
	{
		//printf("BAD!\n");
		ms_clean(shell);
		exit(1);
	}
}