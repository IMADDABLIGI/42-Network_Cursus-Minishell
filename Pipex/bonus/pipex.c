/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:08:33 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/04 02:30:08 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac ,char **av)
{
	int	fd[2];
	int size;
	int	pid;
	int i;

	if (ac == 1)
		perror("Arguments");		
	
	size = ac - 1;
	i = 2;
	// printf("%d\n", size - i);
	// 		printf("fd[0] : %d |  fd[1] : %d", fd[0], fd[1]);
	while ((size - i) != 0)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0 && i == 2)
		{
			// write(1, "here Cmd1\n", 11);
			ft_firstcmd(av[1], av[i], fd);
		}
		else if (pid == 0)
		{
			if ((size - i) == 1)
			{
				// write(1, "here last\n", 11);
				ft_lastcmd(av[i + 1], av[i], fd);
			}
			else
			{	
				// write(1, "here mid\n", 10);
				ft_midcmd(av[i], fd);
			}
		}
		else
		{
			usleep(300);
			// wait(NULL);//Parent Process Must wait for all child Process
			close (fd[0]);
			close (fd[1]);
			// write(1, "here parent\n", 13);
			i++;
		}
	}
}
