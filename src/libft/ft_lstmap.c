/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:18:21 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/26 12:26:37 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*res;
	t_list	*iter;

	if (!lst || !f || !del)
		return (NULL);
	iter = lst;
	tmp = ft_lstnew(f(iter->v));
	if (!tmp)
		return (NULL);
	res = tmp;
	iter = (iter->n);
	while (iter)
	{
		(tmp->n) = ft_lstnew(f(iter->v));
		if (!(tmp->n))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		else
			tmp = (tmp->n);
		iter = (iter->n);
	}
	return (res);
}
