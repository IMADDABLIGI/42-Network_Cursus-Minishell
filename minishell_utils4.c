/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:42:51 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/10 18:51:20 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_check_redirections(t_list *data, t_store *store, int input)
{
	while (data && (data->tatto != 4))
	{
		if (data->tatto == 5)
		{
			ft_creatfile(data);
			if (((input = open(data->next->arg, O_RDONLY)) < 0))
				exit (0);
			else
			{
				dup2(input, STDIN_FILENO);
				close(input); 
			}
		}
		else if (data->tatto == 7)
		{
			ft_creatfile(data);
			store->doc++;
			input = ft_get_heredoc(store->doc, 0, 0);
			if (dup2(input, STDIN_FILENO) < 0)
				write(1, "error\n", 6);
			close(input);
		}
		data = data->next;
	}
	return (input);
}

//---------------------------------------------------------------------------//

int	ft_check_redirections2(t_list *data, int output, t_store *store)
{
	while ((data) && (data->tatto != 4))
	{
		if (output && ((data->tatto == 6) || (data->tatto == 8)))
			close (output);
		if (data->tatto == 6)
		{
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				output = 0;
			else
				output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (data->tatto == 8)
		{
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				output = 0;
			else
				output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		if ((output < 0) && ((store->built) && !(store->pipe)))
			return (-1);
		if (output < 0)
			exit (1);
		data = data->next;
	}
	return (output);
}

