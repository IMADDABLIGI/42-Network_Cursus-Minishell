/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/05 10:34:11 by hznagui          ###   ########.fr       */
=======
/*   Updated: 2023/05/05 10:40:00 by idabligi         ###   ########.fr       */
>>>>>>> 78393c7241aa0d4c16b9843de7b5b80bffe82975
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (data->tatto == 1)
		ft_check_next(data);
	if ((i == 1) && (data->tatto != 5))
		return ;
    // if (data->tatto == 1)
    //     ft_check_next(data, i);
	if (data->tatto == 5)
	{
		if (data->next->next && (data->next->next->tatto == 4))
			exit (0);
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

void	ft_redirect(t_list *data, t_store *store, int i, t_data *a)
{
	int     output;
	t_list  *ptr;

	ptr = data;
	ft_checkinput(data, 0, i);

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

	if ((output = ft_getfile(data, store, i, data)))
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
