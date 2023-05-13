/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools14.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:19:21 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 16:01:54 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_length002(t_data *a)
{
	if ((a->tab[a->i][a->x] == 39 || a->tab[a->i][a->x] == 34) && !a->lock)
	{
		a->lock = 1;
		a->t = a->tab[a->i][a->x];
	}
	else if (a->t == a->tab[a->i][a->x] && a->lock)
	{
		a->lock = 0;
		a->t = '\0';
	}
	else if (((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$'
		&& ft_isdigit(a->tab[a->i][a->x + 1]))
					|| (a->tab[a->i][a->x] == '$' && (a->tab[a->i][a->x
					+ 1] == 39 || a->tab[a->i][a->x + 1] == 34) && !a->lock))
		a->x++;
	else
		a->len++;
}

size_t	ft_length(t_data *a, int *tatto)
{
	a->lock = 0;
	a->x = 0;
	a->len = 0;
	check_tato(a, tatto);
	while (a->tab[a->i][a->x])
	{
		ft_length002(a);
		a->x++;
	}
	return (a->len);
}

/**************************************************************/
void	change2(t_data *a, size_t lock, size_t i)
{
	while (a->strtmp[i])
	{
		if (a->strtmp[i] != 32 && lock == 0)
		{
			a->ret[a->k++] = '"';
			lock = 1;
		}
		else if (a->strtmp[i] == 32 && lock == 1)
		{
			a->ret[a->k++] = '"';
			lock = 0;
		}
		else
		{
			a->ret[a->k] = a->strtmp[i];
			a->k++;
			i++;
		}
	}
	if (lock == 1)
	{
		a->ret[a->k] = '"';
		a->k++;
	}
}
/**************************************************************/

void	ft_change(t_data *a, int index)
{
	a->x++;
	a->strenv = NULL;
	while (a->input[a->x] && (ft_isalnum(a->input[a->x])
			|| a->input[a->x] == '_'))
	{
		a->strenv = ft_strjoin22(a->strenv, a->input[a->x]);
		a->x++;
	}
	a->x--;
	a->strenv = ft_strjoin22(a->strenv, '=');
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp && index == 0)
			change1(a);
		else if (a->strtmp && index == 1)
			change2(a, 0, 0);
		a->tmp = a->tmp->next;
	}
	free(a->strenv);
	return ;
}
/**************************************************************/

void	ft_copie_nb(t_data *a, int index)
{
	int	i;

	i = 0;
	while (a->status[i])
	{
		if (index == 1)
			a->ret[a->k] = a->status[i];
		else
			a->ret1[a->k] = a->status[i];
		i++;
		a->k++;
	}
	free(a->status);
}
