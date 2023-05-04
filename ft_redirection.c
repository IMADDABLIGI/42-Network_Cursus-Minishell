/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/04 10:17:27 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_return_out(int i, int output)
{
	if (((i % 2) == 0))
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	else if (((i % 2) != 0))
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	return (output);
}

//---------------------------------------------------------------------------//

int	ft_check_end(t_list *data, int output, int i)
{
	while (data)
	{
		if ((data->tatto == 6) || (data->tatto == 8))
			return (0);
		if (data->tatto == 5)
		{
			if (!(data->next->next))
				return (ft_return_out(i, 0));
		}
		if (data->tatto == 4)
		{
			if (data->next->tatto == 5)
			{
				if (!(data->next->next->next))
					return (ft_return_out(i, 0));
			}
			if ((data->next->tatto == 6) || (data->next->tatto == 8))
				return (ft_return_out(i, 0));
			return (0);
		}
		data = data->next;
	}
	return (0);
}

//---------------------------------------------------------------------------//


int	ft_getfile(t_list *data, t_store *store, int i, t_list *ptr)
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
	if (output != 0)
		return (output);

	if ((output = ft_check_end(ptr, 0, i)))
		return (output);

	if (i == store->count)
		return (0);
	else if (i == 1)
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	else if ((i % 2) == 0)
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	else if ((i % 2) != 0)
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
			exit (0);
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

void	ft_redirect(t_list *data, t_store *store, int i)
{
	int     output;
	t_list  *ptr;

	ptr = data;
	if (!(ptr->tatto == 1))
	{
		while (ptr && (ptr->tatto != 1))
			ptr = ptr->next;
	}
	ft_checkinput(data, 0, i);
	store->path = ft_getpath(ptr->arg);
	store->arg = ft_arg(ptr);
	if ((output = ft_getfile(data, store, i, data)))
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	execve(store->path, store->arg, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
