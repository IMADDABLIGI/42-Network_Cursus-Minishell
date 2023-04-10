/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:17:54 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/10 17:15:45 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_path(char *path)
{
	if (access(path, F_OK) == 0)// Check if a path to a file is exist or no. 
		return true;
	return false;
}

int	ft_check_cmd(char *cmd)
{
	int		i;
	int		check;
	char	*path;
	char	**s_path;// splitting the variable $PATH with (:) from env command.

	i = 0;
	path = getenv("PATH");
	s_path = ft_split(path, ':');// you're free to use ur own ft_split no problem.
	while (s_path[i])
	{
		if (access(ft_strjoin(s_path[i], cmd), X_OK) == 0)//strjoin has been modified, check it.
			return true;//CMD has been found.
		i++;
	}
	return false;//CMD not found.
}
