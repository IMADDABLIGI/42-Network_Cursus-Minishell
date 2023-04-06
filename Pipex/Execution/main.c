/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:00:58 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/06 23:13:28 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	int 	i;
	t_list	*data;
	(void )ac;

	i = 1;
	while (av[i])
	{
		data = ft_lstadd_back(data, ft_lstnew(av[i], av[i++]));
		i + 2;
	}
	while (data)
	{
		printf("%s ", data->arg);
		data = data->next;
	}
}
