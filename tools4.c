/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:56:16 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 16:56:40 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}
/*----------------------------------------------------------------*/

void	ft_echo(t_list *data)
{
	t_list	*k;
	int		a;

	a = 0;
	k = data;
	k = k->next;
	while (k && ft_check_n(k->arg))
	{
		k = k->next;
		a = 1;
	}
	while (k && k->tatto == 2)
	{
		printf("%s", k->arg);
		k = k->next;
		if (k && k->tatto == 2)
			printf(" ");
	}
	if (!a)
		printf("\n");
	g_global.status = 0;
}
/*----------------------------------------------------------------*/

int	find_(char *a)
{
	int	p;

	p = 0;
	while (a[p])
	{
		if (a[p] == '=')
			return (1);
		p++;
	}
	return (0);
}

void	ft_env(t_data *a, t_list *data)
{
	t_list	*k;

	k = data;
	k = k->next;
	if (k && k->tatto == 2)
	{	
		write(2, "env: ", 6);
		write(2, k->arg, ft_strlen(k->arg));
		write(2, ": No such file or directory\n", 29);
		g_global.status = 127;
	}
	else
	{
		a->tmp = a->e;
		while (a->tmp)
		{
			if (find_(a->tmp->arg))
				printf("%s\n", a->tmp->arg);
			a->tmp = a->tmp->next;
		}
		g_global.status = 0;
	}
}
/*----------------------------------------------------------------*/

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
