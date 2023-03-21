/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_example.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:20:21 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/13 14:34:46 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*str1 = "Hello There 1";
char	*str2 = "Hello There 2";
char	*str3 = "Hello There 3";

int main()
{
	int	i = 0;
	int	pid;
	int	p[2];
	char buff[14];

	if (pipe(p) < 0)
		return (0);
	
	pid = fork();
	
	if (pid == 0)
	{
		close(p[0]);
		write(1, "here Child\n", 12);
        sleep(1);
		write(p[1], str1, 14);
		write(p[1], str2, 14);
		write(p[1], str3, 14);
		close(p[1]);
	}
	
	else
	{
		write(1, "Here Parent\n", 13);
		close(p[1]);
		while (i < 3)
		{
			read(p[0], buff, 14);
			printf("%s\n", buff);
			i++;
		}
		close(p[0]);
	}
	return (0);
}
