/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/21 17:11:45 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

void	ft_check_input(t_store *store, int *fd)
{
	if (store->count != 1)
		dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	close (fd[1]);
}

//---------------------------------------------------------------------------//

void	ft_exec(t_list *data, t_store *store, t_data *a)
{
	while ((store->i <= store->count) && (data))
	{
		if (!ft_check_redirections(data, store, 0))
			return ;
		if (pipe(a->fd) < 0)
			ft_abort(4);
		a->pid = fork();
		if (a->pid == -1)
			ft_abort(3);
		if (a->pid == 0)
			ft_redirect(data, store, a, a->fd);
		else
		{
			ft_check_input(store, a->fd);
			data = ft_get_cmd(data);
			if (store->i == store->count)
			{
				waitpid(a->pid, &g_global.intg, 0);
				ft_check_status();
			}
			store->i++;
		}
	}
}

//---------------------------------------------------------------------------//

int	ft_check_built_input(t_list *data, int input)
{
	while (data)
	{
		if (data->tatto == 5)
		{
			input = open(data->next->arg, O_RDONLY);
			if (input < 0)
				return (0);
			else
				close(input);
		}
		data = data->next;
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_exec_builtins(t_list *data, t_store *store, t_data *a, int fd)
{
	if (ft_check_built_input(data, 0))
	{
		fd = ft_check_redirections2(data, 0, store);
		if (fd)
		{
			if (fd == -1)
				return ;
			store->save = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		ft_execute_builtins(data, a);
		dup2(store->save, STDOUT_FILENO);
		close(store->save);
	}
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store, t_data *a)
{
	if (!(store->count))
		return ;
	if ((store->built) && !(store->pipe))
		ft_exec_builtins(data, store, a, 0);
	else
	{
		store->i = 1;
		a->save_input = dup(STDIN_FILENO);
		ft_exec(data, store, a);
		while (wait(NULL) >= 0)
			;
		dup2(a->save_input, STDIN_FILENO);
		close(a->save_input);
	}
}
