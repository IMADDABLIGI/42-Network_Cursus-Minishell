/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/10 18:50:58 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_checkoutput(t_list *data, t_store *store, int i, int output)
{
	if ((output = ft_check_redirections2(data, 0, store)))
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
	if ((input = ft_check_redirections(data, store, 0)))
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
		store->arg = ft_arg(ptr, ptr, NULL, 0);
	}
	if ((output = ft_checkoutput(data, store, i, 0)))
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}

	if (ft_check_builtins(ptr) == 1)
	{
		ft_execute_builtins(ptr, a);
		exit(0);
	}

	execve(store->path, store->arg, a->env22);
	perror("execve");
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
