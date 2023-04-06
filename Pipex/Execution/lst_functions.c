/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:13:24 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/06 23:23:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *arg, char *tatto)
{
	t_list	*nude;

	nude = malloc(sizeof(t_list));
	if (!nude)
		return (NULL);
	nude->arg = arg;
    nude->tatto = ft_atoi(tatto);
	nude->next = NULL;
	return (nude);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

t_list	*ft_lstadd_back(t_list *lst, t_list *new)
{
	t_list	*ptr;

	ptr = NULL;
	if (lst == NULL)
		lst = new;
	else
	{
		ptr = ft_lstlast(lst);
		ptr->next = new;
	}
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		count;

	count = 0;
	ptr = lst;
	if (!ptr)
		return (0);
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

void	ft_lstdel(t_list **head)
{
	t_list	*ptr;

	ptr = *head;
	while (*head != NULL)
	{
		ptr = ptr->next;
		free(*head);
		*head = ptr;
	}
	return ;
}
