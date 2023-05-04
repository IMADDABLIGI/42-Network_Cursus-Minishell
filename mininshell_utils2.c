/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:08:26 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/04 20:29:45 by idabligi         ###   ########.fr       */
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

void	ft_count(t_list *data, t_store *store)
{
	while (data) 
	{
		if (data->tatto == 4)
			return ;
		if (((data->tatto == 6) || (data->tatto == 8)) && (store->red == 2))
			store->count++;
		else if (data->tatto == 5)
		{
			store->count++;
		}
		data = data->next;
	}
}

/*----------------------------------------------------------------*/

void	ft_check_red1(t_list *data, t_store *store)
{
	data = data->next;
	if (data->next->next)
	{
		if (data->next->next->tatto == 4)
			store->count ++;
	}
}

/*----------------------------------------------------------------*/

void	ft_check_red(t_list *data, t_store *store, int num)
{
	if (data->tatto == 4)
	{
		if (data->next->tatto == 5)
			ft_check_red1(data, store);
		store->red = 0;
		store->num = 0;
		store->num2 = 1;
		store->check = 0;
	}
	if (data->tatto == 5)
		store->red++;
	if ((data->tatto == 5) && (store->red >= 3))
		store->count++;

	
	if ((data->tatto == 5) && (store->check == 0))
	{
		if (!(data->next->next))
		{
			if (((num = open(data->next->arg, O_RDONLY)) < 0))
				ft_printerror(": No such file or directory", data->next->arg);
            store->num = 1;
		}
		else if (store->check == 0)
		{
			if (((num = open(data->next->arg, O_RDONLY)) < 0))
			{
				ft_printerror(": No such file or directory", data->next->arg);
				if (data->next->next && (data->next->next->tatto != 1) && store->num2 && ((data->next->next->tatto != 4)))
					store->count++;
			}
		}
		if (num > 0 && (data->next->next) && (data->next->next->tatto != 1))
			store->num = 1;
		return ;
	}


	else if ((data->tatto == 6) || ((data->tatto == 8)))
	{
		if (store->check == 0)
		{
			if (data->tatto == 6)
			open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (data->tatto == 8)
			open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (store->num == 1)
				store->count++;
			else if ((store->num2 == 0) && ((data->next->next) && (data->next->next->tatto == 4)) && (store->count != 1))
				store->count++;
		}
	}
}

/*----------------------------------------------------------------*/

void	ft_check_fred(t_list *ptr, t_store *store)
{
	while (ptr)
	{
		if (ptr->tatto == 4)
			return ;
		if (ptr->tatto == 5)
		{
			if (ptr->next->next)
			{
				if (ptr->next->next->tatto == 4)
				{
					store->count++;
					return ;
				}
			}
		}
		ptr = ptr->next;
	}
	return ;
}

/*----------------------------------------------------------------*/

void	ft_check_arg(t_list *data, t_store *store)
{
	t_list	*ptr;

	ptr = data;
	store->red = 0;
	store->num = 0;
	store->num2 = 0;
	store->exec = 0;
	store->count = 0;
	store->check = 0;
	ft_check_fred(ptr, store);
	while (ptr)
	{
		if (ptr->tatto == 1)
			store->count++;
		if (ptr->tatto == 4 || ptr->tatto == 5 || ptr->tatto == 6 ||
			ptr->tatto == 7 || ptr->tatto == 8)
			{
				ft_check_red(ptr, store, 0);
				store->exec = 1;
			}
		ptr = ptr->next;
	}
	return ;
}

/*----------------------------------------------------------------*/

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
		ft_abort(1);
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

