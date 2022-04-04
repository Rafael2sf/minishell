/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_ptr_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:28:35 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/31 16:29:35 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ptr_ptr_free(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free (ptr[i++]);
	free(ptr);
}
