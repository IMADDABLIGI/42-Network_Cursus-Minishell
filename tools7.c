/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:16:54 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/18 17:50:56 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_list *data)
{
	char	*cwd;
	t_list	*k;

	k = data;
	k = k->next;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		printf("%s\n", g_global.new_pwd);
	else
		printf("%s\n", cwd);
	if (cwd)
		free(cwd);
	g_global.status = 0;
}
/*----------------------------------------------------------------*/

void	tato(t_data *a)
{
	a->tmp1 = a->p;
	while (a->tmp1)
	{
		if (a->tmp1->tatto == 0)
		{
			a->tmp1->tatto = 1;
			a->tmp1 = a->tmp1->next;
			while (a->tmp1 && a->tmp1->tatto == 0)
			{
				a->tmp1->tatto = 2;
				a->tmp1 = a->tmp1->next;
			}
		}
		else if (a->tmp1->tatto != 4)
		{
			a->tmp1 = a->tmp1->next;
			if (a->tmp1->tatto == 0)
				a->tmp1->tatto = 2;
			a->tmp1 = a->tmp1->next;
		}
		else
			a->tmp1 = a->tmp1->next;
	}
}
/*----------------------------------------------------------------*/

void	create_linked(t_data *a)
{
	t_store	store;

	while (a->tab[a->i])
	{
		a->tmp1 = ft_lstnew(a);
		if (!a->tmp1)
			ft_lstclear(&a->p);
		ft_lstadd_back(&a->p, a->tmp1);
		a->i++;
	}
	if (parse_check(a))
		return ;
	tato(a);
	a->tmp1 = a->p;
	if (!ft_nothing(a->tmp1->arg))
	{
		signal(SIGINT, (void *)sigignore);
		if (ft_check_arg(a->tmp1, &store, a))
			ft_execution(a->tmp1, &store, a);
	}
	else
	{
		printf(" %s: command not found\n", a->tmp1->arg);
		g_global.status = 127;
	}
}
/*----------------------------------------------------------------*/

int	ft_nothing(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] != 32 && a[i] != 9)
			return (0);
		i++;
	}
	return (1);
}
/*----------------------------------------------------------------*/

void	change1(t_data *a)
{
	int	i;

	i = 0;
	while (a->strtmp[i])
	{
		a->ret[a->k] = a->strtmp[i];
		a->k++;
		i++;
	}
}
