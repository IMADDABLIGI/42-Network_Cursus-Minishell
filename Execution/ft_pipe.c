/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:12:17 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 17:48:47 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipefirstcmd(t_list *data)
{
	int	output;

	output = open("/tmp/input", O_WRONLY | O_TRUNC);
	dup2(output, STDOUT_FILENO);
	close (output);
	execve(ft_getpath(data->arg), ft_arg(data), NULL);
}

//---------------------------------------------------------------------------//

void	ft_pipemidllecmd(t_list *data, int i)
{
	int	input;
	int	output;

	if ((i % 2) == 0)
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
	execve(ft_getpath(data->arg), ft_arg(data), NULL);
}

//---------------------------------------------------------------------------//
void	ft_pipelastcmd(t_list *data, int i)
{
	int	input;

	if ((i % 2) == 0)
	{
		input = open("/tmp/input", O_RDONLY);
		dup2(input, STDIN_FILENO);
		close (input);
	}
	else
	{
		input = open("/tmp/output", O_RDONLY);
		dup2(input, STDIN_FILENO);
		close (input);
	}
	execve(ft_getpath(data->arg), ft_arg(data), NULL);
}

//---------------------------------------------------------------------------//