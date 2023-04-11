/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:17:54 by idabligi          #+#    #+#             */
<<<<<<< HEAD:check/ft_check_cmd.c
/*   Updated: 2023/04/10 23:15:29 by idabligi         ###   ########.fr       */
=======
/*   Updated: 2023/04/11 01:55:02 by hznagui          ###   ########.fr       */
>>>>>>> 9225782721a4ef883b2842105fcb6b9b5be7d2dc:Pipex/CHECK/ft_check_cmd.c
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_path(char *path)
{
	if (access(path, X_OK) == 0)// Check if a path to a file is exist or no. 
		return true;
	return false;
}
size_t legnth(char **k)
{
	size_t i;
	
	i=0;
	while (k[i++]);
	return(i);
}
int	ft_check_cmd(char *cmd)
{
	int		i;
	int		check;
	char	*path;
	char *join;
	char	**s_path;// splitting the variable $PATH with (:) from env command.

	i = 0;
	path = getenv("PATH");
	s_path = ft_split(path, ':');// you're free to use ur own ft_split no problem.
	while (s_path[i])
	{
		join=ft_strjoin(s_path[i], cmd);
		if (access(join, X_OK) == 0)//strjoin has been modified, check it.
			return (free_all(s_path,legnth(s_path)),true);
		free(join);//CMD has been found.
		i++;
	}
	return (free_all(s_path,legnth(s_path)),false);//CMD not found.
}
