/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 02:23:30 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec1(t_list *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_lstsize(data) == 2)
			execve(ft_getpath(data->arg), ft_arg(ft_split((data->arg), ' '), data->next->arg), NULL);
		execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return ;
	}
}

//---------------------------------------------------------------------------//

void	ft_exec2(t_list *data, t_store *store)
{
	int		i;
	int		pid;

	i = 1;
	if (open("/tmp/input", O_CREAT, 0644) < 0)
		perror("Error Creating input file");
	if (open("/tmp/output", O_CREAT, 0644) < 0)
		perror("Error Creating output file");
	while(i <= store->count)
	{
		pid = fork();
		if (pid == 0 && i == 1)
			ft_pipefirstcmd(data);
		else if (pid == 0 && i == store->count)
			ft_pipelastcmd(data, i);
		else if (pid == 0)
			ft_pipemidllecmd(data, i);
		else
		{
			waitpid(pid, NULL, 0);
			data = data->next;
			while (data && data->tatto != 1)
				data = data->next;
			i++;
		}
	}
}

//---------------------------------------------------------------------------//

void	ft_exec3(t_list *data, t_store *store)
{
	int		i;
	int		pid;

	i = 1;
	if (open("/tmp/input", O_CREAT, 0644) < 0)
		perror("Error Creating input file");
	if (open("/tmp/output", O_CREAT, 0644) < 0)
		perror("Error Creating output file");
	while(i <= store->count)
	{
		pid = fork();
		if (pid == 0 && i == 1)
			ft_pipefirstcmd(data);
		else if (pid == 0 && i == store->count)
			ft_pipelastcmd(data, i);
		else if (pid == 0)
			ft_pipemidllecmd(data, i);
		else
		{
			waitpid(pid, NULL, 0);
			data = data->next;
			while (data && data->tatto != 1)
				data = data->next;
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
		ft_exec2(data, store);
	else if ((store->exec == 2) && (store->count == 1))
        ft_redcmd(data, 1, 0);
    else if (store->exec == 2)
		ft_exec3(data, store);
}
