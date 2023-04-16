/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:00:58 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/15 21:49:27 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_arg(t_list *data, t_store *store)
{
	t_list  *ptr;

	ptr = data;
	store->exec = 0;
	store->count = 0;
	while (ptr)
	{
		if (ptr->tatto == 1)
			store->count++;
		if ((ptr->tatto == 4)  && (store->exec == 0))
			store->exec = 1;
		if (ptr->tatto == 5 || ptr->tatto == 6  ||
			ptr->tatto == 7  || ptr->tatto == 8)
				store->exec = 2;
		ptr = ptr->next;
	}
}

int	main(int ac, char **av)
{
	int 	i;
	t_list	*data;
	t_store store;

	i = 1;
	if ((ac % 2) == 0)
		write(1 , "Check Argumetns\n", 17);
	while (av[i])
	{
		data = ft_lstadd_back(data, ft_lstnew(av[i], av[i + 1]));
		i += 2;
	}
	ft_check_arg(data, &store);
	ft_execution(data, &store);
}
