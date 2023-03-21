/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:14:31 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/13 18:36:26 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*str1 = "Hello World 1";
char	*str2 = "Hello World 2";
char	*str3 = "Hello World 3";

int main()
{
	int		i = 0;
	int		pid;
	int		size = 14;
	int		p[2];
	char	buff[14];
	int		n;

	if (pipe(p) < 0)
		exit (1);

	if ((pid == fork()) > 0)
	{
		sleep(1);
		// usleep(250000);
		write(1, "Here Parent Process\n", 21);
		write(p[1], str1, 14);
		write(p[1], str2, 14);
		write(p[1], str3, 14);

        close(p[1]);
	}
	else
	{
		write(1, "Here Child Process\n", 20);
		while (i < 3)
		{
			write(1, "Reading\n", 9);
			n = read(p[0], buff, 14);
			printf("%s\n", buff);
			i++;
		}
        close(p[0]);
	}
	return (0);
}