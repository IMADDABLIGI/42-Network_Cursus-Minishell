/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:36:15 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/11 16:58:44 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpath(char *cmd)
{
	int		i;
	char	**p_cmd;
	char	**s_cmd;

	i = 0;
	p_cmd = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	if (cmd[0] == '/')
	{
		if (access((ft_split(cmd, ' ')[0]), X_OK) == 0)
			return (ft_split(cmd, ' ')[0]);
		write(1, "zsh: no such file or directory: ", 33);
		write(1, cmd, ft_strlen(cmd));
		return (NULL);
	}
	if (((cmd[0] == '.') && (cmd[1] == '/')) || ((cmd[0] == '.') && (cmd[1] == '.')))
	{
		if (access((ft_split(cmd, ' ')[0]), X_OK) == 0)
			return (ft_split(cmd, ' ')[0]);
		else if (access((ft_split(cmd, ' ')[0]), F_OK) == 0)
		{
			write(1, "zsh: permission denied: ", 25);
			write(1, cmd, ft_strlen(cmd));
			return (NULL);
		}
		write(1, "zsh: no such file or directory: ", 33);
		write(1, cmd, ft_strlen(cmd));
		return (NULL);
	}
	while (p_cmd[i])
	{
		if (access(ft_strjoin(p_cmd[i], s_cmd[0]), F_OK) == 0)
			return (ft_strjoin(p_cmd[i], s_cmd[0]));
		i++;
	}
	write(1, "zsh: command not found: ", 25);
	write(1, cmd, ft_strlen(cmd));
	return (NULL);
}

char	**ft_arg(char **arg, char *path)
{
	int		i;
	char	**n_arg;

	i = 0;
	while (arg[i])
		i++;
	n_arg = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (arg[i] != NULL)
	{
		n_arg[i] = arg[i];
		i++;
	}
	n_arg[i] = path;
	n_arg[i + 1] = NULL;
	return (n_arg);
}
