/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:11 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/20 17:58:17 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_home(t_list *data, t_data *a, int check)
{
	if (data->next)
		return (0);
	if (!g_global.home)
		printf("cd: HOME not set\n");
	else
	{
		check = chdir(g_global.home);
		if (check == -1)
		{
			printf("cd: %s: No such file or directory\n", g_global.home);
			g_global.status = 1;
		}
		if (g_global.new_pwd)
			free (g_global.new_pwd);
		g_global.new_pwd = ft_strdup(g_global.home);
		ft_re_env(a, NULL, NULL);
	}
	return (1);
}

//---------------------------------------------------------------//

char	*find_cd(t_data *a)
{
	a->tmp = a->e;
	a->strenv = ft_strdup("HOME=");
	while (a->tmp)
	{
		a->strtmp2 = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp2)
		{
			return (free(a->strenv), a->strtmp2);
		}
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), NULL);
}

//---------------------------------------------------------------//

int	ft_lstsize(t_env *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

//---------------------------------------------------------------//

char	**ft_get_env(t_env *env, int len, int i, char **envv)
{
	if (!env)
		return (NULL);
	len = ft_lstsize(env);
	envv = malloc((len + 1) * sizeof(char *));
	if (!envv)
		ft_abort(1);
	while (i < len)
	{
		envv[i] = ft_strdup(env->arg);
		env = env->next;
		i++;
	}
	envv[i] = NULL;
	return (envv);
}
