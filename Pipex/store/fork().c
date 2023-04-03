/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork().c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:22:35 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/17 17:27:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int i = 0;
	int	child1;
	int	child2;

	child1 = fork();
	child2 = fork();

	if (child1 == 0)
	{
		if (child2 == 0)
			printf("Process from child2 of child1 here\n");
		else
			printf("Process from child1 here\n");
	}
	else
	{
		if (child2 == 0)
			printf("Process from child2 of parent here\n");
		else
			printf("Process of parent here\n");
	}
	return (0);
}
