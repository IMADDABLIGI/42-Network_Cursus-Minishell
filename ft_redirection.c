/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/14 21:13:10 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_checkoutput(t_list *data, t_store *store, int i, int output, int *fd)
{
	output = ft_check_redirections2(data, 0, store);
	if (output)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	else if (i != store->count)
		dup2(fd[1], STDOUT_FILENO);
	close (fd[0]);
	close (fd[1]);
	return (output);
}

//---------------------------------------------------------------------------//

void	ft_checkinput(t_list *data, int input, int i, t_store *store)
{
	input = ft_check_redirections(data, store, 0);
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

void	ft_redirect(t_list *data, t_store *store, int i, t_data *a, int *fd)
{
	a->ptr = data;
	signal(SIGQUIT, ft_quit);
	// ft_checkinput(data, 0, i, store);
	if (a->ptr->tatto != 1)
		a->ptr = ft_get_tatto1(a->ptr);
	if (!ft_check_builtins(a->ptr))
	{
		store->path = ft_getpath(a->ptr->arg, NULL, 0, a);
		store->arg = ft_arg(a->ptr, a->ptr, NULL, 0);
	}
	
	ft_checkoutput(data, store, i, 0, fd);

	if (ft_check_builtins(a->ptr) == 1)
	{
		ft_execute_builtins(a->ptr, a);
		exit(g_global.status);
	}
	execve(store->path, store->arg, a->env22);
	perror("execve");
	exit(126);
}

//---------------------------------------------------------------------------//