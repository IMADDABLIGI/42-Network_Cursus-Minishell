/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:12:17 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/08 17:00:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_list *data, int i)
{
	int	input;
	int	output;

	if (i == 1)
	{
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
		dup2(output, STDOUT_FILENO);
		close (output);
	}
	else if ((i % 2) == 0)
	{
		input = open("/tmp/input", O_RDONLY);
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		close (input);
		close (output);
	}
	else if ((i % 2) != 0)
	{
		input = open("/tmp/output", O_RDONLY);
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		close (input);
		close (output);
	}
	if (data->next != NULL)
	{
		write(1, "Here File\n", 8);
		if (data->next->tatto == 2)
			execve(ft_getpath(data->arg), ft_arg(ft_split((data->arg), ' '), data->next->arg), NULL);
	}
		execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
}
