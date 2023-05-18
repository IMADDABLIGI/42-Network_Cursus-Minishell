/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:11 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/18 21:39:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_home(t_list *data, t_data *a, int check)
{
	if (data->next)
		return (0);
	if (!g_global.home)
		printf("cd: HOME not set\n");
	else
	{
		check = chdir(g_global.home);
		if (check == -1)
		{
			printf("cd: %s: No such file or directory\n", g_global.home);
			g_global.status = 1;
		}
		ft_re_env(a, NULL, NULL);
	}
	return (1);
}

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
