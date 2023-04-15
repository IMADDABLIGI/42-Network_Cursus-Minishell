/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:17:54 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/15 16:01:04 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (access(join, X_OK) == 0)
			return (true);//free_all(s_path,legnth(s_path))
		free(join);
		join=NULL;
		i++;
	}
	
	return (false);//CMD not found.
}
