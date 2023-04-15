/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/15 02:51:04 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_getfile(t_list *data, int i)
{
	int	output;

	output = -5;
	while ((data) && (data->tatto != 4))
	{
		if (data->tatto == 6)
			output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (data->tatto == 8)
			output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		data = data->next;
	}
	if ((output == -5) && (i == 1))
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	else if ((output == -5) && ((i % 2) == 0))
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	else if ((output == -5) && ((i % 2) != 0))
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	return (output);
}

//---------------------------------------------------------------------------//

void	ft_checkinput(t_list *data, int i)
{
	int	input;

	if ((i == 1) && (data->tatto != 5))
		return ;
	if (data->tatto == 5)
	{
		if ((input = open(data->next->arg, O_RDONLY)) < 0)
		{
			ft_printerror(": No such file or directory", data->next->arg);
			return ;
		}
		dup2(input, STDIN_FILENO);
		close (input);
		return ;
	}
	else 
	{
		if ((i % 2) == 0)
		{
			input = open("/tmp/input", O_RDONLY);
			dup2(input, STDIN_FILENO);
			close (input);
		}
		else if ((i % 2) != 0)
		{
			input = open("/tmp/output", O_RDONLY);
			dup2(input, STDIN_FILENO);
			close (input);
		}
	}
}

//----------------------------------------------------------------------------//

// void	ft_checkoutput(t_list *data, t_store *store, int i)
// {
// 	int	output;

// 	if (i != store->count)
// 	{
// 		output = ft_getfile(data, i);
// 		printf("%d\n", output);
// 		dup2(output, STDOUT_FILENO);
// 		close(output);
// 	}
// }

//----------------------------------------------------------------------------//

void	ft_redirect(t_list *data, t_store *store, int i)
{
	int	output;

	printf("i : %d\n", i);
	ft_checkinput(data, i);
	if (i != store->count)
	{
		output = ft_getfile(data, i);
		printf("output : %d\n", output);
		if (dup2(output, STDOUT_FILENO) < 0)
			perror("dup2\n");
		close(output);
	}
	usleep(1000);
	if (!(data->tatto == 1))
	{
		while (data && (data->tatto != 1))
			data = data->next;
	}
	execve(ft_getpath(data->arg), ft_arg(data), NULL);
}

//---------------------------------------------------------------------------//

void	ft_redcmd(t_list *data, int pid, int file)
{
	if (data->tatto == 5)
	{
		pid = fork();
		if (pid == 0)
		{
			if ((file = open(data->next->arg, O_RDONLY)) < 0)
			{
				ft_printerror(": No such file or directory", data->next->arg);
				return ;
			}
			dup2(file, STDIN_FILENO);
			close (file);
			execve(ft_getpath(data->next->next->arg), ft_arg(data->next->next), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			file = ft_getfile(data, 0);
			dup2(file, STDOUT_FILENO);
			close(file);
			execve(ft_getpath(data->arg), ft_arg(data), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
}