/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:55:02 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 17:25:14 by hznagui          ###   ########.fr       */
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
/**************************************************************/

void	ft_unset6(t_data *a, t_list *data)
{
	g_global.status = 1;
	write(2, "unset: `", 9);
	write(2, a->kp->arg, ft_strlen(a->kp->arg));
	write(2, "': not a valid identifier\n", 27);
}
