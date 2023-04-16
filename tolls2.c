/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:42:15 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/16 18:11:23 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(t_data *a)
{
	t_list	*p;

	p = malloc (sizeof(t_list));
	if (!p)
		return (0);
	p -> next = NULL;
	p -> tatto = 0;
	p -> arg = str(a,&p->tatto);
	return (p);
}
/*----------------------------------------------------------------*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

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

t_list	*ft_lstclear(t_list **lst)
{
	t_list	*p;

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