/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:14 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/31 13:27:04 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	int		i;
	int		fd[2];
	int		pid;
	char	buff[20];
	char	*arg[] = {"ls", "/Users/idabligi/Desktop/Minishell/Pipex", NULL};
	char	*env[] = {NULL};

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve("/bin/ls", arg, env);
	}
	else
	{
		close(fd[1]);
		while (read())
	}
}