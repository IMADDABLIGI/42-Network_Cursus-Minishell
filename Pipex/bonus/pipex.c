/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:08:33 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/04 01:00:57 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac ,char **av)
{
	int	fd[2];
	int size;
	int	pid;
	int i;

	pipe(fd);
	if (ac == 1)
		perror("Arguments");		
	
	size = ac - 1;
	i = 2;

	close (fd[0]);
	close (fd[1]);

	while ((size - i) != 0)
	{
		pid = fork();
		if (pid == 0 && i == 2)
		{
			ft_firstcmd(av[1], av[i], fd);
		}
		else if (pid == 0)
		{
			if ((size - i) == 1)
				ft_lastcmd(av[i + 1], av[i], fd);
			else
				ft_midcmd(av[i], fd);
		}
		else
		{
			wait(NULL);//Parent Process Must wait for all child Process
			i++;
		}
	}
}
