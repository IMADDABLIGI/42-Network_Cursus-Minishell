/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/13 01:47:42 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

void	ft_redcmd(t_list *data)
{
	int	pid;
	int	input;

	if (data->tatto == 5)
	{
		pid = fork();
		if (pid == 0)
		{
			if ((input = open(data->next->arg, O_RDONLY)) < 0)
			{
				ft_printerror(": No such file or directory", data->next->arg);
				return ;
			}
			dup2(input, STDIN_FILENO);
			close (input);
			execve(ft_getpath(data->next->next->arg), ft_split((data->next->next->arg), ' '), NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}   
}

//---------------------------------------------------------------------------//
