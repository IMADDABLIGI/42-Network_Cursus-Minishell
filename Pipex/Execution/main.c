/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:00:58 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/08 02:24:15 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_arg(t_list *data)
{
	t_list  *ptr;

	ptr = data;
	data->store->exec = 0;
    data->store->i_o = 'F';
	while (data)
	{
		if (data->tatto == 4)
			data->store->exec = 1;
		if (data->tatto == 5 || data->tatto == 6  ||
			data->tatto == 7  || data->tatto == 8)
			{
				data->store->exec = 2;
				break ;
			}
		data = data->next;
	}
}

int	main(int ac, char **av)
{
	int 	i;
	t_list	*data;

	i = 1;
	if ((ac % 2) == 0)
		write(1 , "Check Argumetns\n", 17);
	while (av[i])
	{
		data = ft_lstadd_back(data, ft_lstnew(av[i], av[i + 1]));
		i += 2;
	}
	ft_check_arg(data);
	ft_execution(data);
}
