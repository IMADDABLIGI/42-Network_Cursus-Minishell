/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/04 11:39:18 by idabligi         ###   ########.fr       */
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

void	ft_exec1(t_list *data)
{
	int pid;
	char *path;
	char **arg;

	pid = fork();
	if (pid == 0)
	{
		if (!data)
			return ;
		path = ft_getpath(data->arg);
		arg = ft_arg(data);
		execve(path, arg, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return ;
	}
}

//---------------------------------------------------------------------------//

void	ft_exec3(t_list *data, t_store *store, int i, int pid)
{
	if (!ft_creatfile())
		return ;
	while ((i <= store->count) || !(store->count))
	{
		if (!data)
			return ;
		pid = fork();
		if (pid == 0)
			ft_redirect(data, store, i);
		else
		{
			waitpid(pid, NULL, 0);
			if (data->tatto == 5)
				data = data->next->next;
			data = data->next;
			while (data && (data->tatto != 1) && (data->tatto != 5))
			{
				if ((data->tatto == 6) || (data->tatto == 8))
					ft_creatfile();
				data = data->next;
			}
			if (data)
			{
				if (data->tatto == 5)
					ft_creatfile();
			}
			i++;
		}
	}
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store)
{
	if (!(store->count))
		return ;
	if (store->exec == 0)
		ft_exec1(data);
	else if (store->exec == 1)
		ft_exec3(data, store, 1, 1);
}
