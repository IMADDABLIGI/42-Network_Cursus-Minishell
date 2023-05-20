/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/20 11:55:34 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

void	ft_checkoutput(t_list *data, t_store *store, int *fd, int output)
{
	output = ft_check_redirections2(data, 0, store);
	if (output)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	else if (store->i != store->count)
		dup2(fd[1], STDOUT_FILENO);
	close (fd[0]);
	close (fd[1]);
	return ;
}

//----------------------------------------------------------------------------//

void	ft_redirect(t_list *data, t_store *store, t_data *a, int *fd)
{
	a->ptr = data;
	signal(SIGQUIT, ft_quit);
	if (a->ptr->tatto != 1)
		a->ptr = ft_get_tatto1(a->ptr);
	if (!ft_check_builtins(a->ptr))
	{
		store->path = ft_getpath(a->ptr->arg, NULL, 0, a);
		store->arg = ft_arg(a->ptr, a->ptr, NULL, 0);
	}
	ft_checkoutput(data, store, fd, 0);
	if (ft_check_builtins(a->ptr) == 1)
	{
		ft_execute_builtins(a->ptr, a);
		exit(g_global.status);
	}
    a->env = ft_get_env(a->e, 0, 0, NULL);
	execve(store->path, store->arg, a->env);
	perror("execve");
	exit(126);
}

//---------------------------------------------------------------------------//