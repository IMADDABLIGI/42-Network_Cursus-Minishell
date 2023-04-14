/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 01:07:04 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_getfile(t_list *data)
{
	int	output;

	output = 0;
	// write(1, "here\n", 5);
	while (data)
	{
		if (data->tatto == 6)
			output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (data->tatto == 8)
			output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		data = data->next;
	}
	return (output);
}

//---------------------------------------------------------------------------//

void	ft_redcmd(t_list *data)
{
	int	pid;
	int	input;
	int	output;

	if (data->tatto == 5)
	{
		pid = fork();
		if (pid == 0)
		{
			if ((input = open(data->next->arg, O_RDONLY)) < 0)
			{
				ft_printerror(": No such file or directory", data->next->arg);
				return ;
			}
			dup2(input, STDIN_FILENO);
			close (input);
			execve(ft_getpath(data->next->next->arg), ft_split((data->next->next->arg), ' '), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			output = ft_getfile(data);
			dup2(output, STDOUT_FILENO);
			close(output);
			if (data->next->tatto == 2)
				execve(ft_getpath(data->arg), ft_arg(ft_split((data->arg), ' '),
						data->next->arg), NULL);
			execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

//---------------------------------------------------------------------------//
