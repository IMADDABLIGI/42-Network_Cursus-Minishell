/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:02:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 18:00:22 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*----------------------------------------------------------------*/
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

/*----------------------------------------------------------------*/
void	ft_print(char *arg)
{
	int		i;
	int		z;
	char	p;

	z = 0;
	i = 0;
	p = '"';
	while (arg[i])
	{
		write(1, &arg[i], 1);
		if (arg[i] == '=')
		{
			write(1, &p, 1);
			z = 1;
		}
		i++;
	}
	if (z == 1)
		write(1, &p, 1);
	write(1, "\n", 1);
}

/*----------------------------------------------------------------*/
size_t	ft_unset2(t_data *a, t_list *data)
{
	t_env	*before;
	char	*tmp;
	char	*c;

	before = NULL;
	a->strenv = ft_strdup(data->arg);
	c = ft_strdup(data->arg);
	a->strenv = ft_strjoin22(a->strenv, '=');
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (tmp || !(ft_strcmp(c, a->tmp->arg)))
		{
			if (before)
				before->next = a->tmp->next;
			a->tmp->next = NULL;
			return (free(a->strenv), free(c), free(a->tmp->arg), free(a->tmp),
				1);
		}
		before = a->tmp;
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), free(c), 0);
}

/*----------------------------------------------------------------*/
void	ft_unset(t_list *data, t_data *a)
{
	a->kp = data;
	a->kp = a->kp->next;
	a->tmp = a->e;
	while (a->kp && a->kp->tatto == 2)
	{
		a->i = 0;
		if (!ft_isalpha(a->kp->arg[a->i]))
			ft_unset6(a);
		while (a->kp->arg[a->i] && (ft_isalnum(a->kp->arg[a->i]) == 1
				|| a->kp->arg[a->i] == '_'))
			a->i++;
		if (!a->kp->arg[a->i])
			ft_unset2(a, a->kp);
		else
			ft_unset6(a);
		a->kp = a->kp->next;
	}
}
