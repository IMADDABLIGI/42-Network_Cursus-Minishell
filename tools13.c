/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:10:17 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/14 18:22:16 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export02(t_data *a, char *arg, int index)
{
	if (index == 1)
	{
		free(a->tmp->arg);
		a->tmp->arg = ft_strdup(arg);
	}
	else if (index == 2)
		a->tmp->arg = ft_strjoin(a->tmp->arg,
				ft_strnstr(arg, a->before), 1);
}

size_t	ft_export2(t_data *a, char *arg, int i, int index)
{
	a->strenv = NULL;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
	{
		a->strenv = ft_strjoin22(a->strenv, arg[i]);
		i++;
	}
	a->before = ft_strdup(a->strenv);
	if (index == 1)
		a->strenv = ft_strjoin22(a->strenv, '=');
	else if (index == 2)
		a->before = ft_strjoin(a->before, "+=", 1);
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp2 = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp2 || !(ft_strcmp(a->before, a->tmp->arg)))
		{
			ft_export02(a, arg, index);
			return (free(a->strenv), free(a->before), 1);
		}
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), free(a->before), 0);
}
/**************************************************************/

void	ft_export1(t_data *a, int index)
{
	if (!ft_export2(a, a->kp->arg, 0, index))
	{
		if (index == 2)
			a->kp->arg = ft_withoutplus(a->kp->arg);
		a->tmp = ft_lstnew_env(a->kp->arg);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
	}
}

void	ft_export3(t_data *a)
{
	a->i = 0;
	if (!ft_isalpha(a->kp->arg[a->i]) && a->kp->arg[a->i] != '_')
	{
		ft_printerror(" : not a valid identifier", a->kp->arg);
		g_global.status = 1;
	}
	else
	{
		while (a->kp->arg[a->i] && (ft_isalnum(a->kp->arg[a->i]) == 1
				|| a->kp->arg[a->i] == '_'))
			a->i++;
		if (!a->kp->arg[a->i])
			ft_export1(a, 0);
		else if (a->kp->arg[a->i] == '+' && a->kp->arg[a->i + 1] == '=')
			ft_export1(a, 2);
		else if (a->kp->arg[a->i] != '=')
		{
			ft_printerror(" : not a valid identifier", a->kp->arg);
			g_global.status = 1;
		}
		else
			ft_export1(a, 1);
	}
	a->kp = a->kp->next;
}

void	ft_export(t_list *data, t_data *a)
{
	a->kp = data;
	a->kp = a->kp->next;
	a->tmp = a->e;
	if (a->kp && a->kp->tatto == 2)
	{
		while (a->kp && a->kp->tatto == 2)
			ft_export3(a);
	}
	else
	{
		while (a->tmp)
		{
			write(1, "declare -x ", 11);
			ft_print(a->tmp->arg);
			a->tmp = a->tmp->next;
		}
	}
}
