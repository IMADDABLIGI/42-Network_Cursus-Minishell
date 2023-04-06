/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:54:38 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/05 16:04:35 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_firstcmd(char *infile, char *cmd)
{
	char	*path;
	char	**p_cmd;
	char	**s_cmd;
	int		file;
	int		output;

	file = open(infile, O_RDONLY);
	if (file < 0)
		ft_write_error("Error in file name");
	output = open("/tmp/output", O_WRONLY | O_TRUNC);
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	path = ft_access(p_cmd, s_cmd[0]);
	dup2(file, STDIN_FILENO);
	close (file);
	dup2(output, STDOUT_FILENO);
	close (output);
	execve(path, s_cmd, NULL);
}

void	ft_midcmd(char *cmd, int check)
{
	char	*path;
	char	**p_cmd;
	char	**s_cmd;
	int		input;
	int		output;

	if ((check % 2) != 0)
	{
		input = open("/tmp/output", O_RDONLY);
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	}
	else
	{
		input = open("/tmp/input", O_RDONLY);
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	}
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	path = ft_access(p_cmd, s_cmd[0]);
	dup2(input, STDIN_FILENO);
	close (input);
	dup2(output, STDOUT_FILENO);
	close (output);
	execve(path, s_cmd, NULL);
}

void	ft_lastcmd(char *outfile, char *cmd, int check)
{
	char	*path;
	char	**p_cmd;
	char	**s_cmd;
	int		file;
	int		input;

	file = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((check % 2) != 0)
		input = open("/tmp/output", O_RDONLY);
	else
		input = open("/tmp/input", O_RDONLY);
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	path = ft_access(p_cmd, s_cmd[0]);
	dup2(input, STDIN_FILENO);
	close (input);
	dup2(file, STDOUT_FILENO);
	close (file);
    unlink("/tmp/input");
    unlink("/tmp/output");
	execve(path, s_cmd, NULL);
}
