/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:57:51 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/14 18:31:25 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_check2(t_data *a)
{
	if (a->tmp1->tatto != 0 && !a->tmp1->next)
	{
		printf("\e[1;31m parse error!\n\e[0m");
		g_global.status = 258;
		return (1);
	}
	else if (a->tmp1->tatto == 4 && (a->tmp1->next->tatto == 4))
	{
		printf("\e[1;31m parse error!\n\e[0m");
		g_global.status = 258;
		return (1);
	}
	else if ((a->tmp1->tatto != 0 && a->tmp1->tatto != 4)
		&& a->tmp1->next->tatto != 0)
	{
		printf("\e[1;31m parse error!\n\e[0m");
		g_global.status = 258;
		return (1);
	}
	a->tmp1 = a->tmp1->next;
	return (0);
}

int	parse_check(t_data *a)
{
	a->tmp1 = a->p;
	if (a->tmp1->tatto == 4)
	{
		printf("\e[1;31m parse error!\n\e[0m");
		g_global.status = 258;
		return (1);
	}
	while (a->tmp1)
	{
		if (parse_check2(a))
			return (1);
	}
	return (0);
}
/**************************************************************/

void	str2(t_data *a)
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
					+ 1] == 39 || a->tab[a->i][a->x + 1] == 34)
					&& !a->lock))
		a->x++;
	else
	{
		a->ret[a->k] = a->tab[a->i][a->x];
		a->k++;
	}
}

char	*str(t_data *a, int *tatto)
{
	a->ret = malloc(sizeof(char) * ft_length(a, tatto));
	if (!a->ret)
		ft_abort(1);
	a->k = 0;
	a->lock = 0;
	a->x = 0;
	while (a->tab[a->i][a->x])
	{
		str2(a);
		a->x++;
	}
	a->ret[a->k] = '\0';
	return (a->ret);
}
/**************************************************************/

size_t	strlen_expand(char *str)
{
	size_t	i;
	size_t	len;
	int		lock;

	lock = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] != 32 && str[i] != 9) && lock == 0)
		{
			lock = 1;
			len += 2;
		}
		else if ((str[i] == 32 || str[i] == 9) && lock == 1)
			lock = 0;
		i++;
		len++;
	}
	return (len);
}
