/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:00:58 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/08 17:13:19 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_arg(t_list *data, t_store *store)
{
	t_list  *ptr;

	ptr = data;
    store->exec = 4;
    store->count = 2;
	// while (ptr)
	// {
	// 	if (ptr->tatto == 4)
	// 	{
	// 		data->store->exec = 1;
	// 		break ;
	// 	}
	// 	if (ptr->tatto == 5 || ptr->tatto == 6  ||
	// 		ptr->tatto == 7  || ptr->tatto == 8)
	// 		{
	// 			data->store->exec = 2;
	// 			break ;
	// 		}
	// 	ptr = ptr->next;
	// }
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


	// while (data)
	// {
	// 	printf("%s t-> %d\n", data->arg, data->tatto);
	// 	data = data->next;
	// }