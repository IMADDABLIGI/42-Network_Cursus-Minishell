/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:55:02 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 15:56:55 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_strlencmd(t_list *ptr, int i)
{
	while ((ptr) && (ptr->tatto != 4))
	{
		if ((ptr->tatto == 5) || (ptr->tatto == 6) || (ptr->tatto == 7)
			|| (ptr->tatto == 8))
			ptr = ptr->next->next;
		else
		{
			ptr = ptr->next;
			i++;
		}
	}
	return (i);
}
