/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 17:01:58 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_checkoutput(t_list *data, t_store *store, int i, int output)
{
	output = ft_check_redirections2(data, 0, store);
	if (output)
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

void	ft_redirect(t_list *data, t_store *store, int i, t_data *a)
{
	t_list	*ptr;

	ptr = data;
	ft_checkinput(data, 0, i, store);
	if (ptr->tatto != 1)
		ptr = ft_get_tatto1(ptr);
	if (!ft_check_builtins(ptr))
	{
		store->path = ft_getpath(ptr->arg, NULL, 0);
		store->arg = ft_arg(ptr, ptr, NULL, 0);
	}
	a->output = ft_checkoutput(data, store, i, 0);
	if (a->output)
	{
		dup2(a->output, STDOUT_FILENO);
		close(a->output);
	}
	if (ft_check_builtins(ptr) == 1)
	{
		ft_execute_builtins(ptr, a);
		exit(g_global.status);
	}
	execve(store->path, store->arg, a->env22);
	perror("execve");
	exit(126);
}

//---------------------------------------------------------------------------//