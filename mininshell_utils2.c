/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:08:26 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/17 01:24:54 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printerror(char *str, char *cmd)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
/*----------------------------------------------------------------*/

void	ft_check_arg(t_list *data, t_store *store)
{
	t_list	*ptr;

	ptr = data;
	store->exec = 0;
	store->count = 0;
	while (ptr)
	{
		if (ptr->tatto == 1)
			store->count++;
		if ((ptr->tatto == 4) && (store->exec == 0))
			store->exec = 1;
		if (ptr->tatto == 5 || ptr->tatto == 6 ||
			ptr->tatto == 7 || ptr->tatto == 8)
			store->exec = 2;
		ptr = ptr->next;
	}
}

/*----------------------------------------------------------------*/

char	*ft_getpath(char *cmd)
{
	int		i;
	char	**p_cmd;

	i = 0;
	p_cmd = ft_split(getenv("PATH"), ':', cmd);
	if (cmd[0] == '/')
	{
		if (access((ft_split(cmd, ' ', NULL)[0]), X_OK) == 0)
			return (ft_split(cmd, ' ', NULL)[0]);
		ft_printerror(": No such file or directory", cmd);
	}
	if (((cmd[0] == '.') && (cmd[1] == '/')) || ((cmd[0] == '.')
			&& (cmd[1] == '.')))
	{
		if (access((ft_split(cmd, ' ', NULL)[0]), X_OK) == 0)
			return (ft_split(cmd, ' ', NULL)[0]);
		else if (access((ft_split(cmd, ' ', NULL)[0]), F_OK) == 0)
			ft_printerror(": Permission denied", cmd);
		else
			ft_printerror(": No such file or directory", cmd);
	}
	else
	{
		while (p_cmd[i])
		{
			if (access(p_cmd[i], X_OK) == 0)
				return (p_cmd[i]);
			i++;
		}
		ft_printerror(": command not found", cmd);
	}
	return (NULL);
}

/*----------------------------------------------------------------*/

char	**ft_arg(t_list *data)
{
	int		i;
	t_list	*ptr;
	char	**arg;

	i = 0;
	ptr = data;
	while ((ptr) && (ptr->tatto != 4) && (ptr->tatto != 5) &&
			(ptr->tatto != 6) && (ptr->tatto != 7) && (ptr->tatto != 8))
	{
		ptr = ptr->next;
		i++;
	}
	arg = malloc((i + 1) * sizeof(char *));
	if (!arg)
		exit (1);
	i = 0;
	while ((data) && (data->tatto != 4) && (data->tatto != 5) &&
			(data->tatto != 6) && (data->tatto != 7) && (data->tatto != 8))
	{
		arg[i++] = ft_strdup(data->arg);
		data = data->next;
	}
	arg[i] = NULL;
	return (arg);
}

//---------------------------------------------------------------------------//

int	ft_check_cmd(t_list *data)
{
	while (data && (data->tatto != 4))
	{
		if (data->tatto == 1)
		{
			if (!ft_getpath((data->arg)))
				return (0);
		}
		data = data->next;
	}
	return (1);
}
