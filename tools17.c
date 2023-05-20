/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools17.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:07:42 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/20 14:02:59 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_data *a, char *str)
{
	a->tmp = ft_lstnew_env(str);
	if (!a->tmp)
		ft_abort(1);
	ft_lstadd_back_env(&a->e, a->tmp);
}

//---------------------------------------------------------------//
int	ft_shlvl(t_data *a)
{
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp2 = ft_strnstr(a->tmp->arg, "SHLVL=");
		if (a->strtmp2)
		{
			if (check(a->strtmp2) || check_nothing(a->strtmp2, 0, 0))
				return (free(a->tmp->arg), a->tmp->arg = ft_strdup("SHLVL=1")
					, 1);
			else if (0 > ft_atoi(a->strtmp2))
				return (free(a->tmp->arg), a->tmp->arg = ft_strdup("SHLVL=0")
					, 1);
			else
				return (free(a->tmp->arg), a->tmp->arg = ft_strjoin("SHLVL=",
						ft_itoa(ft_atoi(a->strtmp2) + 1), 0), 1);
		}
		else if (!(ft_strcmp("SHLVL", a->tmp->arg)))
			return (free(a->tmp->arg), a->tmp->arg = ft_strdup("SHLVL=1"), 1);
		a->tmp = a->tmp->next;
	}
	add_to_env(a, "SHLVL=1");
	return (0);
}
