/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/07 02:49:14 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec1(t_list *data)
{
	int	pid;
	int	infile;

	pid = fork();
	if (pid == 0)
	{
		if (ft_lstsize(data) == 2)
		{
			infile = open(data->next->arg, O_RDONLY);
			dup2(infile, STDIN_FILENO);
		}
		execve(ft_getpath(data->arg), ft_split((data->arg), ' '), NULL);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return ;
	}
}

void	ft_execution(t_list *data)
{
	// if (data->exec == 0)
		ft_exec1(data);
	// else if (data->exec == 1)
	// 	ft_exec2(data);
	// else
	// 	ft_exec3(data);
}
