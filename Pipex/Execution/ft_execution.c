/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/08 17:15:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_exec1(t_list *data)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (ft_lstsize(data) == 2)
// 			execve(ft_getpath(data->arg), ft_arg(ft_split((data->arg), ' '), data->next->arg), NULL);
// 		execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, 0);
// 		return ;
// 	}
// }


void	ft_exec2(t_list *data, t_store *store)
{
	int		pid;
	int		i;

	i = 1;
	open("/tmp/input", O_CREAT, 0644);
	open("/tmp/output", O_CREAT, 0644);
	while(i <= store->count)
	{
		if (data->tatto == 1)
			pid = fork();
		if (pid == 0)
		{
			write(1, "child\n", 6);
			printf("CMD : %s\n", data->arg);
			printf("%d\n", i);
			ft_pipe(data, i);
		}
		else
		{
			waitpid(pid, NULL, 0);
			write(1, "Parent\n", 7);
			data = data->next;
			while (data && data->tatto != 1)
				data = data->next;
			i++;
		}
	}
}


void	ft_execution(t_list *data, t_store *store)
{
	// if (store->exec == 0)
	// 	ft_exec1(data);
	// else if (store->exec == 1)
		ft_exec2(data, store);
	// else
	// 	ft_exec3(data);
}
