/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:11:41 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/21 17:11:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------//

char	*find_cd(t_data *a)
{
	a->tmp = a->e;
	a->strenv = ft_strdup("HOME=");
	while (a->tmp)
	{
		a->strtmp2 = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp2)
		{
			return (free(a->strenv), a->strtmp2);
		}
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), NULL);
}

//---------------------------------------------------------------//

void	ft_status(int num)
{
	if (num == -2)
		g_global.status = 1;
}

//---------------------------------------------------------------//

int	ft_go_path(t_list *data, char *pwd, char *path, int check)
{
	path = ft_strjoin2(pwd, data->next->arg);
	check = chdir(path);
	free(path);
	return (check);
}

//---------------------------------------------------------------//

void	ft_check_status(void)
{
	if (WIFEXITED(g_global.intg))
		g_global.status = WEXITSTATUS(g_global.intg);
	else if (WIFSIGNALED(g_global.intg))
		ft_handle_sig(WTERMSIG(g_global.intg));
}
