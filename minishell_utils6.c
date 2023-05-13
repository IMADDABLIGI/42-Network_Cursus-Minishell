/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:52:45 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 13:47:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_old_path(char *path, int check, int i, int j)
{
	char	*n_path;

	check = chdir(g_global.old_pwd);
	if (check > 0)
		return (check);
	free (g_global.new_pwd);
		g_global.new_pwd = g_global.old_pwd;
	ft_print_error2();
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
