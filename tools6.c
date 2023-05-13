/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:08:51 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 17:33:13 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_builtins(t_list *data, t_data *a)
{
	while (data && (data->tatto != 1))
		data = data->next;
	if (!ft_strcmp(data->arg, "cd"))
		ft_cd(data, NULL, a);
	else if (!ft_strcmp(data->arg, "echo"))
		ft_echo(data);
	else if (!ft_strcmp(data->arg, "export"))
		ft_export(data, a);
	else if (!ft_strcmp(data->arg, "exit"))
		ft_exit(data, a);
	else if (!ft_strcmp(data->arg, "env"))
		ft_env(a, data);
	else if (!ft_strcmp(data->arg, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(data->arg, "unset"))
		ft_unset(data, a);
}
/*----------------------------------------------------------------*/

int	ft_check_builtins(t_list *data)
{
	if (!ft_strcmp(data->arg, "echo") || !ft_strcmp(data->arg, "cd")
		|| !ft_strcmp(data->arg, "pwd") || !ft_strcmp(data->arg, "export")
		|| !ft_strcmp(data->arg, "unset") || !ft_strcmp(data->arg, "env")
		|| !ft_strcmp(data->arg, "exit"))
		return (1);
	return (0);
}
/*----------------------------------------------------------------*/

void	check_tato(t_data *a, int *tatto)
{
	if (!ft_strcmp(a->tab[a->i], ">>"))
		*tatto = 8;
	else if (!ft_strcmp(a->tab[a->i], "<<"))
		*tatto = 7;
	else if (!ft_strcmp(a->tab[a->i], "<"))
		*tatto = 5;
	else if (!ft_strcmp(a->tab[a->i], ">"))
		*tatto = 6;
	else if (!ft_strcmp(a->tab[a->i], "|"))
		*tatto = 4;
}
/*----------------------------------------------------------------*/

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*----------------------------------------------------------------*/

char	*ft_strnstr(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;
	char	*p;

	p = haystack;
	j = 0;
	i = 0;
	while (p[i + j] && needle[j])
	{
		if (p[i + j] == needle[j])
			j++;
		else if (p[i + j] == '=')
			return (0);
		else
			return (0);
	}
	if (needle[j] == '\0')
		return (p + j);
	else
		return (0);
}
