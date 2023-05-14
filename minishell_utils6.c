/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:52:45 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 18:40:34 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_old_path(char *path, int check, int i, int j)
{
	char	*n_path;

	n_path = NULL;
	check = chdir(g_global.old_pwd);
	if (check > 0)
		return (check);
	free (g_global.new_pwd);
		g_global.new_pwd = g_global.old_pwd;
	while (path[i])
		i++;
	i--;
	while (path[i] && (path[i] != '/') && (i > 0))
		i--;
	n_path = malloc((i + 1) * sizeof(char));
	if (!n_path)
		ft_abort(1);
	while (path[j] && (j != i))
	{
		n_path[j] = path[j];
		j++;
	}
	n_path[j] = '\0';
	g_global.old_pwd = n_path;
	return (-2);
}

//---------------------------------------------------------------------------//

int	ft_check_red2(t_list *data, int fd)
{
	if (data->tatto == 6)
		fd = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (data->tatto == 8)
		fd = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		ft_printerror(": Is a directory", data->next->arg);
	close(fd);
	return (fd);
}

//---------------------------------------------------------------------------//

t_list	*ft_get_tatto1(t_list *ptr)
{
	while (ptr && (ptr->tatto != 1))
	{
		if (ptr->tatto == 4)
			exit(1);
		ptr = ptr->next;
	}
	if (ptr && (ptr->tatto != 1))
		exit(1);
	return (ptr);
}

//---------------------------------------------------------------------------//

void	ft_init_store(t_store *store)
{
	store->pipe = 0;
	store->built = 0;
	store->count = 0;
	store->check = 0;
}

//---------------------------------------------------------------------------//

char	*ft_get_path2(char *cmd)
{
	if ((cmd[0] == '.') && (cmd[1] == '/') && (cmd[2] == '\0'))
		write(2, "./: is a directory\n", 20);
	else if (access((cmd), X_OK) == 0)
		return (cmd);
	else if (access((cmd), F_OK) == 0)
		ft_printerror(": Permission denied", cmd);
	else
		ft_printerror(": No such file or directory", cmd);
	exit(126);
}
