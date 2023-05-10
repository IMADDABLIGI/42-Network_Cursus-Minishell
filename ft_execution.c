/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/10 12:39:22 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_creatfile(t_list *data)
{
	if ((data->tatto == 5 || data->tatto == 6) && !ft_strcmp(data->next->arg, "/dev/stdout"))
		return (1);
	unlink("/tmp/input");
	unlink("/tmp/output");
	if (open("/tmp/input", O_CREAT, 0644) < 0)
	{
		perror("Error Creating input file");
		exit (1);
	}
	if (open("/tmp/output", O_CREAT, 0644) < 0)
	{
		perror("Error Creating output file");
		exit (1);
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_exec(t_list *data, t_store *store, int i, int pid, t_data *a)
{
	ft_creatfile(data);
	while ((i <= store->count) && (data))
	{
		if ((pid = fork()) == -1)
		{
			perror("fork");
			return ;	
		}
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
					ft_creatfile(data);
				data = data->next;
			}
			if ((data) && (data->tatto == 4))
				data = data->next;
			i++;
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
			if (((input = open(data->next->arg, O_RDONLY)) < 0))
				return (0);
			else
				close (input);
		}
		data = data->next;
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store,t_data *a , int fd)
{
	if (!(store->count))
		return ;
	if ((store->built) && !(store->pipe))//just IN Parent
	{
		if (ft_check_built_input(data, 0))
		{		
			if ((fd = ft_checkoutput(data, store, 1, 0)))
			{
				store->save = dup(STDOUT_FILENO);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			ft_execute_builtins(data, a);
			dup2(store->save, STDOUT_FILENO);
			close(store->save);
		}
	}
	else
	{
		// write(1, "here2\n", 6);
		ft_exec(data, store, 1, 1, a);
	}
}
