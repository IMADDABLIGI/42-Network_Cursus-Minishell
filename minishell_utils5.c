/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:48:03 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/11 15:11:32 by idabligi         ###   ########.fr       */
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
	// printf("arg %s\n", path);
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

void	ft_cd(t_list *data, int check, char *path, char *pwd)
{
	pwd = ft_initial_cd(NULL, NULL);
	// printf("OLDPWD=%s\n", global.old_pwd);
	if (data->next)
	{
		if ((data->next->tatto == 5) || (data->next->tatto == 6) || (data->next->tatto == 7)
			|| (data->next->tatto == 8) || (data->next->tatto == 4))
			return ;
		if ((data->next->arg[0] == '~') && (data->next->arg[1] == '\0'))
			check = chdir("/Users/idabligi");

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
	// printf("NEWPWD=%s\n", global.new_pwd);
	if (pwd)
	{
		if (global.new_pwd)
			free (global.new_pwd);
		global.new_pwd = getcwd(NULL, 0);
	}
	// printf("NEWPWD=%s\n", global.new_pwd);
	// ft_re_env();
}