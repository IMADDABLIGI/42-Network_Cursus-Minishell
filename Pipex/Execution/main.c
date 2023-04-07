/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:00:58 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/07 00:55:00 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_arg(t_list *data)
{
    t_list  *ptr;

    ptr = data;
    data->exec = 0;
    while (data)
    {
        if (data->tatto == 4)
            data->exec = 1;
        if (data->tatto == 5 || data->tatto == 6  ||
            data->tatto == 7  || data->tatto == 8)
            {
                data->exec = 2;
                break ;
            }
    }
}


int	main(int ac, char **av)
{
	int 	i;
	t_list	*data;
	(void )ac;

	i = 1;
	while (av[i])
	{
		data = ft_lstadd_back(data, ft_lstnew(av[i], av[i + 1]));
		i += 2;
	}
    // ft_check_arg(data);
	while (data)
	{
		printf("%s t-> : %d\n", data->arg, data->tatto);
		data = data->next;
	}
}
