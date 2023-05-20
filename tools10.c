/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:10:24 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/20 14:00:39 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_quote2(t_data *a)
{
	if ((a->input[a->i] == 39 || a->input[a->i] == 34) && a->lock == 0)
	{
		a->lock = 1;
		a->z = 1;
		a->t = a->input[a->i];
	}
	else if ((a->input[a->i] == 39 || a->input[a->i] == 34) && (a->lock == 1))
	{
		if (a->input[a->i] == a->t)
		{
			a->z = 0;
			a->lock = 0;
		}
	}
	a->i++;
}

void	open_quote(t_data *a)
{
	a->z = 0;
	a->i = 0;
	a->lock = 0;
	a->t = '\0';
	while (a->input[a->i])
		open_quote2(a);
	if (a->z == 1)
	{
		printf("\e[1;31m open quotes!\n\e[0m");
		g_global.status = 258;
	}
	else
	{
		if (!ft_separit(a))
			free_all22(a->tab, a->length);
		ft_lstclear(&a->p);
	}
}
/*----------------------------------------------------------------*/

int	ft_separit(t_data *a)
{
	if (!ft_split22(a))
		return (ft_abort(1), 1);
	a->i = 0;
	a->p = NULL;
	create_linked(a);
	return (0);
}
/*----------------------------------------------------------------*/

void	ft_create_env(t_data *a, char **env)
{
	a->i = 0;
	while (env[a->i])
	{
		a->tmp = ft_lstnew_env(env[a->i]);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
		a->i++;
	}
	if (!a->e)
	{
		a->pwd = getcwd(NULL, 0);
		if (!a->pwd)
			a->tmp = ft_lstnew_env(ft_strjoin("getcwd: cannot access parent",
						" directories: No such file or directory", 7));
		else
			a->tmp = ft_lstnew_env(ft_strjoin("PWD=", a->pwd, 2));
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
		add_to_env(a, "_=/usr/bin/env");
		add_to_env(a, "SHLVL=1");
	}
	else
		ft_shlvl(a);
}
/*----------------------------------------------------------------*/

void	handler(int status)
{
	g_global.status = 1;
	(void)status;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
