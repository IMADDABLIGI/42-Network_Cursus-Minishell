/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:42:15 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/16 14:46:39 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_lstnew(t_data *a)
{
	t_arg	*p;

	p = malloc (sizeof(t_arg));
	if (!p)
		return (0);
	p -> next = NULL;
	p -> tatto = 0;
	p -> arg = str(a,&p->tatto);
	return (p);
}
/*----------------------------------------------------------------*/

void	ft_lstadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*p;

	if (!lst || !new)
		return ;
	else if (*lst == 0)
		*lst = new;
	else
	{
		p = *lst;
		while (p -> next)
		{
			p = p -> next;
		}
		p -> next = new ;
	}
}
/*----------------------------------------------------------------*/

t_arg	*ft_lstclear(t_arg **lst)
{
	t_arg	*p;

	if (!lst)
		return (0);
	while ((*lst))
	{
		p = (*lst);
		*lst = (*lst)->next;
		free(p->arg);
		free (p);
	}
	return (0);
}