/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:59:15 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 10:00:45 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nbr_of_words223(t_data *a)
{
	if (!a->lock1)
	{
		a->t = a->input[a->k];
		a->lock1 = 1;
		if (a->lock == 1)
			a->length--;
		a->lock = 1;
	}
	else if (a->input[a->k] == a->t && a->lock1)
	{
		a->lock = 0;
		a->lock1 = 0;
		if (!a->input[a->k + 1] || a->input[a->k + 1] == ' ' || a->input[a->k
				+ 1] == '<' || a->input[a->k + 1] == '>' || a->input[a->k
				+ 1] == '|')
			a->length++;
	}
}

void	nbr_of_words222(t_data *a)
{
	if (a->input[a->k] != 39 && a->input[a->k] != 34 && a->input[a->k] != ' '
		&& a->input[a->k] != '<' && a->input[a->k] != '>'
		&& a->input[a->k] != '|' && a->lock == 0)
	{
		a->length++;
		a->lock = 1;
	}
	else if (a->input[a->k] == 39 || a->input[a->k] == 34)
		nbr_of_words223(a);
}

size_t	nbr_of_words22(t_data *a)
{
	a->k = 0;
	a->lock = 0;
	a->lock1 = 0;
	a->length = 0;
	a->t = '\0';
	while (a->input[a->k])
	{
		if (a->input[a->k] != 39 && a->input[a->k] != 34
			&& a->input[a->k] != ' ' && a->input[a->k] != '<'
			&& a->input[a->k] != '>' && a->input[a->k] != '|' && a->lock == 0)
			nbr_of_words222(a);
		else if ((a->input[a->k] == '<' || a->input[a->k] == '>'
				|| a->input[a->k] == '|') && !a->lock1)
		{
			if ((a->input[a->k] == '<' && a->input[a->k + 1] == '<')
				|| (a->input[a->k] == '>' && a->input[a->k + 1] == '>'))
				a->k += 1;
			a->length++;
			a->lock = 0;
		}
		else if (a->input[a->k] == ' ' && a->lock == 1 && a->lock1 == 0)
			a->lock = 0;
		a->k++;
	}
	return (a->length);
}
/*----------------------------------------------------------------*/

void	ft_return222(t_data *a)
{
	while ((((a->input[a->end] != '<' && a->input[a->end] != '>'
					&& a->input[a->end] != '|' && a->input[a->end] != ' ')
				|| a->lock1 == 1) && a->input[a->end] != '\0'))
	{
		if ((a->input[a->end] == 39 || a->input[a->end] == 34) && !a->lock1)
		{
			a->t = a->input[a->end];
			a->lock1 = 1;
		}
		else if (a->lock1 && a->t == a->input[a->end])
			a->lock1 = 0;
		a->end++;
	}
}

char	**ft_return22(t_data *a)
{
	a->i = 0;
	a->start = 0;
	while (a->i < a->length)
	{
		while (a->input[a->start] == ' ' && a->input[a->start] != '\0')
			a->start++;
		a->end = a->start;
		if ((a->input[a->end] == '<' || a->input[a->end] == '>'
				|| a->input[a->end] == '|' || a->input[a->end] == ' '))
		{
			if ((a->input[a->end] == '<' && a->input[a->end + 1] == '<')
				|| (a->input[a->end] == '>' && a->input[a->end + 1] == '>'))
				a->end += 1;
			a->end++;
		}
		else
			ft_return222(a);
		a->tab[a->i] = ft_substr(a->input, a->start, a->end - a->start);
		if (!a->tab[a->i])
			return (free_all22(a->tab, a->i));
		a->i++;
		a->start = a->end;
	}
	a->tab[a->i] = NULL;
	return (a->tab);
}
