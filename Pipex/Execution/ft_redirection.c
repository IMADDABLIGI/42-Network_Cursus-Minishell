/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 17:38:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_getfile(t_list *data)
{
	int	output;

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
			execve(ft_getpath(data->arg), ft_arg(data), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			file = ft_getfile(data);
			dup2(file, STDOUT_FILENO);
			close(file);
			execve(ft_getpath(data->arg), ft_arg(data), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

//---------------------------------------------------------------------------//

// void	ft_checkinput(t_list *data, t_store store, int i)
// {
// 	int	input;

// 	if (i == 1)
// 		return (0);
// 	if (data->tatto == 5)
// 	{
// 		if ((input = open(data->next->arg, O_RDONLY)) < 0)
// 		{
// 			ft_printerror(": No such file or directory", data->next->arg);
// 			return ;
// 		}
// 		dup2(input, STDIN_FILENO);
// 		close (input);
// 		return ;
// 	}
// 	else 
// 	{
// 		if ((i % 2) == 0)
// 		{
// 			input = open("/tmp/input", O_RDONLY);
// 			dup2(input, STDIN_FILENO);
// 			close (input);
// 		}
// 		else if ((i % 2) != 0)
// 		{
// 			input = open("/tmp/output", O_RDONLY);
// 			dup2(input, STDIN_FILENO);
// 			close (input);
// 		}
// 	}
// }

// //---------------------------------------------------------------------------//

// void	ft_firstred(t_list *data)
// {
// 	int	input;
// 	int	output;

// 	if (data->tatto == 5)
// 	{
// 		if ((input = open(data->next->arg, O_RDONLY)) < 0)
// 		{
// 			ft_printerror(": No such file or directory", data->next->arg);
// 			return ;
// 		}
// 		dup2(input, STDIN_FILENO);
// 		close (input);
// 	}
// }


// //---------------------------------------------------------------------------//

// void	ft_redirect(t_list *data, t_store store, int i)
// {
// 	int	input;
// 	int	output;

// 	  if (data->tatto != 5)
// 	  {
		
// 	  }


// }

//---------------------------------------------------------------------------//
