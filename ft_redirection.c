/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/01 21:51:10 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_check_end(t_list *data, int output, int i)
{
	while (data)
	{
		if (data->tatto == 4)
		{
			if ((data->next->tatto == 6) || (data->next->tatto == 8))
			{
				if ((output == 0) && ((i % 2) == 0))
					output = open("/tmp/output", O_WRONLY | O_TRUNC);
				else if ((output == 0) && ((i % 2) != 0))
					output = open("/tmp/input", O_WRONLY | O_TRUNC);
				return (output);
			}
		}
		data = data->next;
	}
	return (0);
}

//---------------------------------------------------------------------------//

int	ft_getfile(t_list *data, t_store *store, int i)
{
	int	output;

	output = 0;
	while ((data) && (data->tatto != 4))
	{
		if (data->tatto == 6)
			output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (data->tatto == 8)
			output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		data = data->next;
	}
	if ((output == 0) && (i == store->count))
		output = ft_check_end(data, 0, i);
	else if ((output == 0) && (i == 1))
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	else if ((output == 0) && ((i % 2) == 0))
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	else if ((output == 0) && ((i % 2) != 0))
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	return (output);
}

//---------------------------------------------------------------------------//

void	ft_checkinput(t_list *data, int input, int i)
{
	if ((i == 1) && (data->tatto != 5))
		return ;
	if (data->tatto == 5)
	{
		if ((input = open(data->next->arg, O_RDONLY)) < 0)
		{
			ft_printerror(": No such file or directory", data->next->arg);
			exit (0) ;
		}
		dup2(input, STDIN_FILENO);
		close(input);
		return ;
	}
	else
	{
		if ((i % 2) == 0)
			input = open("/tmp/input", O_RDONLY);
		else if ((i % 2) != 0)
			input = open("/tmp/output", O_RDONLY);
		dup2(input, STDIN_FILENO);
		close(input);
	}
}

//----------------------------------------------------------------------------//

void	ft_nocmd(t_list *data)
{
	if (data->tatto == 5)
	{
		if ((open(data->next->arg, O_RDONLY)) < 0)		
			ft_printerror(": No such file or directory", data->next->arg);
	}
	else if (data->tatto == 6 || data->tatto == 8)
		open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

//----------------------------------------------------------------------------//

void	ft_redirect(t_list *data, t_store *store, int i)
{
	int     output;
	t_list  *ptr;

	ptr = data;
	if (!store->count)
	{
		ft_nocmd(data);
		exit (0);
	}
	if (!(ptr->tatto == 1))
	{
		while (ptr && (ptr->tatto != 1))
			ptr = ptr->next;
	}
	store->path = ft_getpath(ptr->arg);
	store->arg = ft_arg(ptr);
	ft_checkinput(data, 0, i);
	if ((output = ft_getfile(data, store, i)))
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	execve(store->path, store->arg, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
