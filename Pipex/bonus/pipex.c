/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:08:33 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/05 16:05:24 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int	size;
	int	pid;
	int	i;

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
			ft_firstcmd(av[1], av[i]);
		else if (pid == 0)
		{
			if ((size - i) == 1)
				ft_lastcmd(av[i + 1], av[i], i);
			ft_midcmd(av[i], i);
		}
		else
			waitpid(pid, NULL, 0);
		i++;
	}
}
