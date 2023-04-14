/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:36:15 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 17:52:22 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpath(char *cmd)
{
	int		i;
	char	**p_cmd;

	i = 0;
	p_cmd = ft_split(getenv("PATH"), ':');
	if (cmd[0] == '/')
	{
		if (access((ft_split(cmd, ' ')[0]), X_OK) == 0)
			return (ft_split(cmd, ' ')[0]);
		ft_printerror(": No such file or directory", cmd);
	}
	if (((cmd[0] == '.') && (cmd[1] == '/')) || ((cmd[0] == '.') && (cmd[1] == '.')))
	{
		if (access((ft_split(cmd, ' ')[0]), X_OK) == 0)
			return (ft_split(cmd, ' ')[0]);
		else if (access((ft_split(cmd, ' ')[0]), F_OK) == 0)
			ft_printerror(": Permission denied", cmd);
		else
			ft_printerror(": No such file or directory", cmd);
	}
	else 
	{	
		while (p_cmd[i])
		{
			if (access(ft_strjoin(p_cmd[i], cmd), F_OK) == 0)
				return (ft_strjoin(p_cmd[i], cmd));
			i++;
		}
		ft_printerror(": command not found", cmd);
	}
	return (NULL);
}

char	**ft_arg(t_list *data)
{
	int		i;
	char	**n_arg;
	t_list *ptr;

	ptr = data;
	i = 0;
	while ((data) && (data->tatto != 5) && (data->tatto != 6) && (data->tatto != 7) && (data->tatto != 8) && (data->tatto != 4))
	{
		i++;
		data = data->next;
	}
	n_arg = malloc((i + 1) * sizeof(char *));
	i = 0;
	while ((ptr) && (ptr->tatto != 5) && (ptr->tatto != 6) && (ptr->tatto != 7) && (ptr->tatto != 8) && (ptr->tatto != 4))
	{
		n_arg[i] = ptr->arg;
		ptr = ptr->next;
		i++;
	}
	n_arg[i + 1] = NULL;
	i = 0;
	return (n_arg);
}
