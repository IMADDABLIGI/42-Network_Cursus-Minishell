/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:08:26 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/12 09:52:28 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printerror(char *str, char *cmd)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

/*-------------------------------------------------------------------------------------*/

void	ft_check_red(t_list *data, t_store *store, int fd)
{
	if ((data->tatto == 1) && (ft_check_builtins(data)))
		store->built = 1;
	else if (data->tatto == 4)
	{
		store->pipe = 1;
		store->check = 0;
	}
	else if ((data->tatto == 5) && !store->check)
	{
		if (((fd = open(data->next->arg, O_RDONLY)) < 0))
			ft_printerror(": No such file or directory", data->next->arg);
		close (fd);
	}
	else if (((data->tatto == 6) || (data->tatto == 8)) && !store->check)
	{
		if (data->tatto == 6)
			fd = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (data->tatto == 8)
			fd = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			ft_printerror(": Is a directory", data->next->arg);
		close (fd);
	}
	if (fd < 0)
		store->check = 1;
}

/*-------------------------------------------------------------------------------------*/

void	ft_check_arg(t_list *data, t_store *store)
{
	t_list	*ptr;

	ptr = data;
	store->pipe = 0;
	store->built = 0;
	store->count = 0;
	store->check = 0;
	ft_run_doc(data, store);
	while (ptr)
	{
		if ((ptr->tatto == 1) && !(store->count))
			store->count++;
		if (ptr->tatto == 4)
		{
			if (store->count == 0)
				store->count += 2;
			else
				store->count++;
		}
		if (ptr->tatto == 4 || ptr->tatto == 5 || ptr->tatto == 6
			|| ptr->tatto == 8 || ptr->tatto == 1)
				ft_check_red(ptr, store, 0);
		ptr = ptr->next;
	}
}

/*-------------------------------------------------------------------------------------*/


char	*ft_getpath(char *cmd)
{
	int		i;
	char	**p_cmd;

	i = 0;
	if (cmd[0] == '/')
	{
		if (access((cmd), X_OK) == 0)
			return (cmd);
		ft_printerror(": No such file or directory", cmd);
	}
	else if (((cmd[0] == '.') && (cmd[1] == '/')) || ((cmd[0] == '.')
			&& (cmd[1] == '.')))
	{
		if (access((cmd), X_OK) == 0)
			return (cmd);
		else if (access((cmd), F_OK) == 0)
			ft_printerror(": Permission denied", cmd);
		else
			ft_printerror(": No such file or directory", cmd);
	}
	else
	{
		p_cmd = ft_split_cmd(getenv("PATH"), ':', cmd);
		while (p_cmd[i])
		{
			if (access(p_cmd[i], X_OK) == 0)
				return (p_cmd[i]);
			i++;
		}
		ft_printerror(": command not found", cmd);
	}
	exit (1);
}

/*----------------------------------------------------------------*/

char	**ft_arg(t_list *data, t_list *ptr, char **arg, int i)
{
	while ((ptr) && (ptr->tatto != 4))
	{
		if ((ptr->tatto == 5) || (ptr->tatto == 6) || (ptr->tatto == 7) || (ptr->tatto == 8))
			ptr=ptr->next->next;
		else
		{	
			ptr = ptr->next;
			i++;
		}
	}
	arg = malloc((i + 1) * sizeof(char *));
	if (!arg)
		ft_abort(1);
	i = 0;
	while ((data) && (data->tatto != 4))
	{
		if ((data->tatto == 5) || (data->tatto == 6) || (data->tatto == 7) || (data->tatto == 8))
			data = data->next->next;
		else 
		{
			arg[i++] = ft_strdup(data->arg);
			data = data->next;
		}
	}
	arg[i] = NULL;
	return (arg);
}

