/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:11 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/20 19:00:35 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_home(t_list *data, t_data *a, int check, int tat)
{
	if (data->next && !tat)
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
	if (!tat)
		return (1);
	return (-3);
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

//---------------------------------------------------------------//

char	*find_oldpwd(t_data *a)
{
	a->tmp = a->e;
	a->strenv = ft_strdup("OLDPWD=");
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

int	ft_go_oldpath(t_list *data, t_data *a, int check)
{
	char	*old;
	if (data->next->arg[0] == '-' && data->next->arg[1] == '-' && data->next->arg[2] == '\0')
		check = ft_cd_home(data, a, 0, 1);
	else if (data->next->arg[0] == '-' && data->next->arg[1] == '\0')
	{
		old = find_oldpwd(a);
		printf("%s\n", old);
		if (!old)
		{
			write(2, "cd: OLDPWD not set\n", 20);
			return (-2);
		}
		check = chdir(old);
		return (1);
	}
	else
	{
		printf("cd: %s: invalid option\n", data->next->arg);
		return (-2);
	}
	return (check);
}
