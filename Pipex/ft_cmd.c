/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:54:38 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/01 22:26:09 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_firstcmd(char *infile, char *cmd)
{
	char	*path;
	char	**p_cmd;
	char	**s_cmd;
	int		file;

	file = open(infile, O_RDONLY);
	if (file < 0)
		ft_write_error("Error in file name");
	dup2(file, STDIN_FILENO);
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	path = ft_access(p_cmd, s_cmd[0]);
	execve(path, s_cmd, NULL);
}

void	ft_secoundcmd(char *infile, char *cmd)
{
	char	*path;
	char	**p_cmd;
	char	**s_cmd;
	int		file;

	file = open(infile, O_WRONLY);
	if (file < 0)
		ft_write_error("Error in file name2");
	dup2(file, STDOUT_FILENO);
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	path = ft_access(p_cmd, s_cmd[0]);
	execve(path, s_cmd, NULL);
}
