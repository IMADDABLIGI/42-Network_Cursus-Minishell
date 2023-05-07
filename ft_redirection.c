/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/07 12:34:36 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_check_redirections(t_list *data, int output)
{
	while ((data) && (data->tatto != 4))
	{
		if (data->tatto == 6)
		{
			if (output)
				close (output);
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				output = 0;
			else
				output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (data->tatto == 8)
		{
			if (output)
				close (output);
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				output = 0;
			else
				output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		data = data->next;
	}
	return (output);
}

//---------------------------------------------------------------------------//

int	ft_checkoutput(t_list *data, t_store *store, int i, int output)
{
	if ((output = ft_check_redirections(data, 0)))
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

void	ft_checkinput(t_list *data, int input, int i, t_store *store)
{

	while (data && (data->tatto != 4))
	{
		if ((data->tatto == 5) && ((store->built == 0) || (store->pipe == 1)))
		{
            ft_creatfile(data);
			if ((open(data->next->arg, O_RDONLY)) < 0)
				exit (0);
			if ((open(data->next->arg, O_RDONLY)) >= 0)
			{
				input = open(data->next->arg, O_RDONLY);
				dup2(input, STDIN_FILENO);
				close(input); 
			}
		}
		if (data->tatto == 7)
		{
			store->doc++;
			input = ft_get_heredoc(data, store->doc, 0, 0);
			open("heredoc", O_RDONLY);
			if (dup2(input, STDIN_FILENO) < 0)
				write(1, "error\n", 6);
			close(input); 
		}
		data = data->next; 
	}
	
	if (input)
		return ;
	else
	{
		if (i == 1)
		    return ;
		if ((i % 2) == 0)
			input = open("/tmp/input", O_RDONLY);
		else if ((i % 2) != 0)
			input = open("/tmp/output", O_RDONLY);
		dup2(input, STDIN_FILENO);
		close(input);
	}
}

//----------------------------------------------------------------------------//

void	ft_redirect(t_list *data, t_store *store, int i, t_data *a)
{
	int     output;
	t_list  *ptr;

	ptr = data;
	ft_checkinput(data, 0, i, store);

	if (!(ptr->tatto == 1))
	{
		while (ptr && (ptr->tatto != 1))
		{
			if (ptr->tatto == 4)
				exit (0);
			ptr = ptr->next;
		}
		if (ptr && (ptr->tatto != 1))
			exit (0);
	}
	if (ft_check_builtins(ptr) == 0)
	{
		store->path = ft_getpath(ptr->arg);
		store->arg = ft_arg(ptr);
	}

	if ((output = ft_checkoutput(data, store, i, 0)))
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}

	if (ft_check_builtins(ptr) == 1)
	{
		ft_execute_builtins(ptr,a);
		exit(0);
	}

	execve(store->path, store->arg, a->env22);
	perror("execve");
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
