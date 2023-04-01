/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:13:33 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/30 15:57:46 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	int		fd[2];
	int		pid;
	char	buff[500];
	int		i = 0;
	char	*str[] = {"ghjd", "-l","/Users/idabligi/Desktop/Minishell/Pipex"};
	char	*env[] = {NULL};

	pipe(fd);
	
	pid = fork();
	
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve("/bin/ls", str, env);
	}
	else
	{
		close (fd[1]);
		while (read(fd[0], buff, 1))
		{
			printf("%s", buff);
		}	
		close (fd[0]);
	}
}