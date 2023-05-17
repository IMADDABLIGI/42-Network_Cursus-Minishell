/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:48:03 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/17 20:01:09 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------//

char	*ft_initial_cd(char *pwd, t_data *a)
{
	a->check = 0;
	g_global.home = find_cd(a);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (g_global.old_pwd)
			free(g_global.old_pwd);
		g_global.old_pwd = pwd;
	}
	return (pwd);
}

//---------------------------------------------------------------//

int	ft_get_home(t_list *data, char *path, int check)
{
	struct stat	sb;

	path = ft_strjoin3(g_global.home, data->next->arg);
	stat(path, &sb);
	if (S_ISREG(sb.st_mode))
	{
		printf("cd: %s: Not a directory\n", path);
		free(path);
		return (-2);
	}
	check = chdir(path);
	if (check == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(path);
		return (-2);
	}
	free(path);
	return (1);
}

//---------------------------------------------------------------//

void	ft_re_env(t_data *a, char *old_path, char *new_path)
{
	old_path = ft_strjoin("OLDPWD=", g_global.old_pwd, 3);
	new_path = ft_strjoin("PWD=", g_global.new_pwd, 3);
	if (!ft_export2(a, old_path, 0, 1))
	{
		a->tmp = ft_lstnew_env(old_path);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
	}
	if (!ft_export2(a, new_path, 0, 1))
	{
		a->tmp = ft_lstnew_env(new_path);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
	}
	free(old_path);
	free(new_path);
}

//---------------------------------------------------------------//

int	ft_cds(t_list *data, char *pwd, int check, char *path)
{
	if (!ft_check_dr(data->next->arg))
		return (-2);
	if (data->next->tatto == 5 || data->next->tatto == 6 || data->next->tatto
		== 7 || data->next->tatto == 8 || data->next->tatto == 4)
		check = chdir(g_global.home);
	else if ((data->next->arg[0] == '~') && (data->next->arg[1] == '\0'))
		check = chdir(g_global.home);
	else if ((data->next->arg[0] == '~') && (data->next->arg[1] == '/'))
		check = ft_get_home(data, NULL, 0);
	else if (!pwd && (data->next->arg[0] == '.') && data->next->arg[1] == '\0')
		ft_print_error2();
	else if (data->next->arg[0] == '/')
		check = chdir(data->next->arg);
	else if (!pwd && (data->next->arg[0] == '.') && (data->next->arg[1] == '.')
		&& (data->next->arg[2] == '\0'))
		check = ft_cd_old_path(g_global.old_pwd, 0, 0, 0);
	else if (!pwd)
		return (-2);
	else
	{
		path = ft_strjoin2(pwd, data->next->arg);
		check = chdir(path);
		free(path);
	}
	return (check);
}

//---------------------------------------------------------------//

void	ft_cd(t_list *data, char *pwd, t_data *a)
{
	pwd = ft_initial_cd(NULL, a);
	if (ft_cd_home(data, a, 0) && !data->next)
		return ;
	else if (data->next)
		a->check = ft_cds(data, pwd, 0, NULL);
	if (a->check == -2)
	{
		g_global.status = 1;
		return ;
	}
	if (a->check == -1)
	{
		if (data->next)
			printf("cd: %s: No such file or directory\n", data->next->arg);
		g_global.status = 1;
		return ;
	}
	if (pwd || (!pwd && (data->next->arg[0] == '.')
			&& (data->next->arg[1] == '.') && (data->next->arg[2] == '\0')))
	{
		if (g_global.new_pwd)
			free(g_global.new_pwd);
		g_global.new_pwd = getcwd(NULL, 0);
	}
	ft_re_env(a, NULL, NULL);
}
