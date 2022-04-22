/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:17:22 by daalmeid          #+#    #+#             */
/*   Updated: 2022/04/22 10:13:35 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	nbr_len(int n)
{
	int		i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	tk_is_last(t_ast *tk)
{
	return (!tk->prev || (tk->prev->right == tk && !tk->prev->prev));
}
