/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:56:01 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/14 12:05:44 by idabligi         ###   ########.fr       */
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
	while (data && (data->tatto != 4))
	{
		if ((data->tatto == 6) || (data->tatto == 8))
			ft_creatfile(data);
		data = data->next;
	}
	return (data);
}
