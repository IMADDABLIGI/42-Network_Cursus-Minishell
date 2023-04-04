/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:08:33 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/04 18:27:39 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac ,char **av)
{
	int size;
	int	pid;
	int i;

	if (ac == 1)
		perror("Arguments");		
	open("/tmp/input", O_CREAT, 0644);
	open("/tmp/output", O_CREAT, 0644);
	size = ac - 1;
	i = 2;
	while ((size - i) != 0)
	{
		pid = fork();
		if (pid == 0 && i == 2)
		{
			write(1, "here starts\n", 13);
			ft_firstcmd(av[1], av[i]);
		}
		else if (pid == 0)
		{
			if ((size - i) == 1)
			{
				write(1, "here LAST\n", 11);
				ft_lastcmd(av[i + 1], av[i], i);
			}
			else
			{	
				write(1, "here middle\n", 13);
				ft_midcmd(av[i], i);
			}
		}
		else
		{
			usleep(300);
			write(1, "here parent\n", 13);
			i++;
		}
	}
}
