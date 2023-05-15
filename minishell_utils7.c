/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:56:01 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/15 11:03:10 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quit(int sig)
{
	(void)sig;
}

//---------------------------------------------------------------------------//

void	ft_handle_sig(int sig)
{
	if (sig == 3)
	{
		write(2, "Quit: 3\n", 9);
		g_global.status = 131;
	}
}

//---------------------------------------------------------------------------//

t_list	*ft_get_cmd(t_list *data)
{
	if (data->tatto == 5)
		data = data->next;
	data = data->next;
	while (data && (data->tatto != 4))
		data = data->next;
	if ((data) && (data->tatto == 4))
		data = data->next;
	return (data);
}
