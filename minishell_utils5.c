/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:48:03 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/12 14:44:06 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glb global;

//---------------------------------------------------------------//

char	*ft_initial_cd(char *pwd, char *home)
{
	if (!home)
		global.home = getenv("HOME");
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (global.old_pwd)
			free (global.old_pwd);
		global.old_pwd = pwd;
	}
	return (pwd);
}

//---------------------------------------------------------------//

int ft_get_home(t_list *data, char *path, int check)
{
	path = ft_strjoin3(global.home, data->next->arg);
	check = chdir(path);
	if (check == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (-2);
	}
	free (path);
	return (1);
}

//---------------------------------------------------------------//

int	ft_check_dr(char *path)
{
	struct stat sb;

	stat(path, &sb);
	if (S_ISREG(sb.st_mode))
	{
    	printf("cd: %s: Not a directory\n", path);
		return (0);
	}
	return (1);
}
//---------------------------------------------------------------//

void	ft_re_env(t_data *a,char *old_path,char *new_path)
{
	old_path = ft_strjoin("OLDPWD=",global.old_pwd,3);
	new_path = ft_strjoin("PWD=",global.new_pwd,3);
			if (!ft_export2(a,old_path,0,1))
				{
					a->tmp = ft_lstnew_env(old_path);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e,a->tmp);
				}
			if (!ft_export2(a,new_path,0,1))
				{
					a->tmp = ft_lstnew_env(new_path);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e,a->tmp);
				}
}


//---------------------------------------------------------------//

void	ft_cd(t_list *data, int check, char *path, char *pwd,t_data *a)
{
	pwd = ft_initial_cd(NULL, NULL);
	(void)a;
	// printf("OLDPWD=%s\n", global.old_pwd);
	if (data->next)
	{
		if (!ft_check_dr(data->next->arg))
			return ;
		if ((data->next->tatto == 5) || (data->next->tatto == 6) || (data->next->tatto == 7)
			|| (data->next->tatto == 8) || (data->next->tatto == 4))
				check = chdir(global.home);
		else if ((data->next->arg[0] == '~') && (data->next->arg[1] == '\0'))
			check = chdir(global.home);

		else if ((data->next->arg[0] == '~') && (data->next->arg[1] == '/'))
			check = ft_get_home(data, NULL, 0);
		
		else if ((pwd == NULL) && (data->next->arg[0] == '.') && (data->next->arg[1] == '\0'))
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");

		else if (data->next->arg[0] == '/')
			check = chdir(data->next->arg);

		else if (!pwd && (data->next->arg[0] == '.') && (data->next->arg[1] == '.') && (data->next->arg[2] == '\0'))
			check = chdir(global.old_pwd);

		else
		{
			if (!pwd)
				check = -1;
			else
			{
				path = ft_strjoin2(pwd, data->next->arg);
				check = chdir(path);
				free (path);
			}
		}
	}
	else
		check = chdir(global.home);
	if (check == -1)
	{
		if (data->next)
			printf("cd: %s: No such file or directory\n", data->next->arg);
		else
			perror("cd ");
		return ;
	}
	if (check == -2)
		return ;
	if (pwd || (!pwd && (data->next->arg[0] == '.') && (data->next->arg[1] == '.') && (data->next->arg[2] == '\0')))
	{
		if (global.new_pwd)
			free (global.new_pwd);
		global.new_pwd = getcwd(NULL, 0);
	}
	// printf("NEWPWD=%s\n", global.new_pwd);
	ft_re_env(a,NULL,NULL);
}