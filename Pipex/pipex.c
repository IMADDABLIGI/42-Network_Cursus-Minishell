/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:44:19 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/02 15:48:38 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *arg1, char *arg2[])
{
	execve(arg1, arg2, NULL);
}

int main(int ac, char **av)
{
	int		pid;
	int		fd[2];

    if (ac < 5)
        ft_write_error("Error in Arguments");
	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close (fd[0]);
		// close (fd[1]);
		ft_firstcmd(av[1], av[2], fd[1]);
	}
	else
	{
		wait(NULL);
		close (fd[1]);
		// close (fd[0]);
		ft_secoundcmd(av[4], av[3], fd[0]);
	}
}
