/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:08:26 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/14 11:05:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printerror(char *str, char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

//---------------------------------------------------------------------------//

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
		fd = open(data->next->arg, O_RDONLY);
		if (fd < 0)
			ft_printerror(": No such file or directory", data->next->arg);
		close(fd);
	}
	else if (((data->tatto == 6) || (data->tatto == 8)) && !store->check)
		fd = ft_check_red2(data, 0);
	if (fd < 0)
	{
		g_global.status = 1;
		store->check = 1;
	}
	else if (fd > 0)
		g_global.status = 0;
}

//---------------------------------------------------------------------------//

int	ft_check_arg(t_list *data, t_store *store, t_data *a)
{
	t_list	*ptr;

	ptr = data;
	ft_init_store(store);
	if (!ft_run_doc(data, store, a))
		return (0);
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
	return (1);
}

//---------------------------------------------------------------------------//

char	*ft_getpath(char *cmd, char **p_cmd, int i, t_data *a)
{
	if (cmd[0] == '/')
	{
		if (access((cmd), X_OK) == 0)
			return (cmd);
		ft_printerror(": No such file or directory", cmd);
		exit(127);
	}
	else if (((cmd[0] == '.') && (cmd[1] == '/')) || ((cmd[0] == '.')
			&& (cmd[1] == '.')))
		return (ft_get_path2(cmd));
	else
	{
		p_cmd = ft_split_cmd(find_path(a), ':', cmd);
		if (p_cmd)
		{
			while (p_cmd[i])
			{
				if (access(p_cmd[i], X_OK) == 0)
					return (p_cmd[i]);
				i++;
			}
		}
		ft_printerror(": command not found", cmd);
		exit(127);
	}
}

/*-----------------------------------------------------------*/

char	**ft_arg(t_list *data, t_list *ptr, char **arg, int i)
{
	i = ft_get_strlencmd(ptr, 0);
	arg = malloc((i + 1) * sizeof(char *));
	if (!arg)
		ft_abort(1);
	i = 0;
	while ((data) && (data->tatto != 4))
	{
		if ((data->tatto == 5) || (data->tatto == 6) || (data->tatto == 7)
			|| (data->tatto == 8))
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
