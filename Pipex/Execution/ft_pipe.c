/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:12:17 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/08 02:48:06 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_list *data)
{
	int	input;
	int	output;

	if (data->store->i_o == 'F')
	{
		data->store->i_o = 'I';
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
		dup2(output, STDOUT_FILENO);
	}
	else if (data->store->i_o == 'I')
	{
		data->store->i_o = 'O';
		input = open("/tmp/intput", O_RDONLY);
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
	}
	else if (data->store->i_o == 'O')
	{
		data->store->i_o = 'I';
		input = open("/tmp/output", O_RDONLY);
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
	}
	if (data->next != NULL)
	{
		if (data->next->tatto == 2)
			execve(ft_getpath(data->arg), ft_arg(ft_split((data->arg), ' '), data->next->arg), NULL);
	}
		execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
}
