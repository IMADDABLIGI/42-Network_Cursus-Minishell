/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/16 18:32:26 by hznagui          ###   ########.fr       */
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
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(ft_getpath(data->arg), ft_arg(data), NULL);
	else
	{
		waitpid(pid, NULL, 0);
		return ;
	}
}

//---------------------------------------------------------------------------//

void	ft_exec2(t_list *data, t_store *store, int i)
{
	int	pid;

	if (!ft_creatfile())
		return ;
	while (i <= store->count)
	{
		if (!ft_getpath((data->arg)))
			return ;
		pid = fork();
		if ((pid == 0) && (i == 1))
			ft_pipefirstcmd(data);
		else if (pid == 0 && i == store->count)
			ft_pipelastcmd(data, i);
		else if (pid == 0)
			ft_pipemidllecmd(data, i);
		else
		{
			waitpid(pid, NULL, 0);
			data = data->next;
			while (data && (data->tatto != 1))
				data = data->next;
			i++;
		}
	}
}

//---------------------------------------------------------------------------//

void	ft_exec3(t_list *data, t_store *store, int i)
{
	int	pid;

	if (!ft_creatfile())
		return ;
	while (i <= store->count)
	{
		if (!ft_check_cmd(data))
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
				if ((data->tatto == 6) || (data->tatto == 8)
					|| (data->tatto == 5))
					ft_creatfile();
				data = data->next;
			}
			i++;
		}
	}
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store)
{
	if (store->exec == 0)
		ft_exec1(data);
	else if (store->exec == 1)
		ft_exec2(data, store, 1);
	else if (store->exec == 2)
		ft_exec3(data, store, 1);
}
