/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:37:19 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/20 18:45:33 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

size_t	ft_expand_length(t_data *a, int index)
{
	char	*tmp;

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
		tmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (tmp && index == 0)
			return (free(a->strenv), ft_strlen(tmp));
		else if (tmp && index == 1)
			return (free(a->strenv), strlen_expand(tmp));
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), 0);
}
/**************************************************************/

void	ft_length2(t_data *a)
{
	if ((a->t == '"' || !a->t) && a->input[a->x] == '$'
		&& a->input[a->x + 1] == '?')
	{
		a->status = ft_itoa(g_global.status);
		a->len += ft_strlen(a->status);
		free(a->status);
		a->x++;
	}
	else if ((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1]
		&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
				+ 1] == '_') && !is_expanded(a))
		a->len += ft_expand_length(a, 0);
	else if ((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1]
		&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
				+ 1] == '_') && !is_expanded(a))
		a->len += ft_expand_length(a, 1);
	else
		a->len++;
}
/**************************************************************/

size_t	ft_length1(t_data *a)
{
	a->lock = 0;
	a->x = 0;
	a->t = '\0';
	a->len = 0;
	while (a->input[a->x])
	{
		if ((a->input[a->x] == 39 || a->input[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->input[a->x];
		}
		else if (a->t == a->input[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		ft_length2(a);
		a->x++;
	}
	return (a->len);
}
/**************************************************************/

void	ft_expand2(t_data *a)
{
	if ((a->t == '"' || !a->t) && a->input[a->x] == '$'
		&& a->input[a->x + 1] == '?')
	{
		ft_copie_nb(a, 1);
		a->x++;
	}
	else if (((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1]
			&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_')) && !is_expanded(a))
		ft_change(a, 0);
	else if (((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1]
			&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_')) && !is_expanded(a))
		ft_change(a, 1);
	else
	{
		a->ret[a->k] = a->input[a->x];
		a->k++;
	}
	a->x++;
}
/**************************************************************/

char	*expand(t_data *a)
{
	a->ret = malloc(sizeof(char) * ft_length1(a) + 1);
	if (!a->ret)
		ft_abort(1);
	a->k = 0;
	a->lock = 0;
	a->x = 0;
	while (a->input[a->x])
	{
		if ((a->input[a->x] == 39 || a->input[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->input[a->x];
		}
		else if (a->t == a->input[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		ft_expand2(a);
	}
	a->ret[a->k] = '\0';
	return (free(a->input), a->ret);
}
