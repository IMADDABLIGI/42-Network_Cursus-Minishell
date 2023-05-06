/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/06 17:37:48 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_creatfile(void)
{
	unlink("/tmp/input");
	unlink("/tmp/output");
	if (open("/tmp/input", O_CREAT, 0644) < 0)
	{
		perror("Error Creating input file");
		return (0);
	}
	if (open("/tmp/output", O_CREAT, 0644) < 0)
	{
		perror("Error Creating output file");
		return (0);
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_exec1(t_list *data, t_store *store, t_data *a)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (!data)
			return ;
		if (!ft_check_builtins(data))
		{
		store->path = ft_getpath(data->arg);
		store->arg = ft_arg(data);
        execve(store->path, store->arg, a->env22);
		perror("execve");
		exit(EXIT_FAILURE);
		}
		else 
		{
			ft_execute_builtins(data,a);
			exit(0);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		return ;
	}
}

//---------------------------------------------------------------------------//

void	ft_exec3(t_list *data, t_store *store, int i, int pid,t_data *a)
{
	if (!ft_creatfile())
		return ;
	while ((i <= store->count))
	{
		if (!data)
			return ;
		pid = fork();
		if (pid == 0)
			ft_redirect(data, store, i,a);
		else
		{
			waitpid(pid, NULL, 0);
			if (data->tatto == 5)
				data = data->next;
			data = data->next;
			while (data && (data->tatto != 4))
			{
				if ((data->tatto == 6) || (data->tatto == 8))
					ft_creatfile();
				data = data->next;
			}
			if ((data) && (data->tatto == 4))
				data = data->next;
			if ((data) && (data->tatto == 5))
				ft_creatfile();
			i++;
		}
	}
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store,t_data *a , int fd)
{
    int save;

	if (!(store->count))
		return ;

    if ((store->built) && !(store->pipe))
    {
        ft_checkinput(data, 0, 1, store);
        if ((fd = ft_checkoutput(data, store, 1, 0)))
        {
            save = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        ft_execute_builtins(data, a);
        dup2(save, STDOUT_FILENO);
        close(save);
    }

	else if (store->exec == 0)
		ft_exec1(data, store,a);
	else if (store->exec == 1)
		ft_exec3(data, store, 1, 1, a);
}
