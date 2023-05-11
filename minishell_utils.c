/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/11 11:26:33 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glb global;

//---------------------------------------------------------------//

char	*ft_initial_cd(char *pwd, char *home)
{
	home = NULL;
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

void	ft_cd(t_list *data, int check, char *path, char *pwd)
{
	pwd = ft_initial_cd(NULL, NULL);
	printf("OLDPWD=%s\n", global.old_pwd);
	if (data->next)
	{
		if ((data->next->tatto == 5) || (data->next->tatto == 6) || (data->next->tatto == 7)
			|| (data->next->tatto == 8) || (data->next->tatto == 4))
			return ;
		if ((data->next->arg[0] == '~') && (data->next->arg[1] == '\0'))
			check = chdir("/Users/idabligi");
		else if ((pwd == NULL) && (data->next->arg[0] == '.') && (data->next->arg[1] == '\0'))
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		else if (data->next->arg[0] == '/')
			check = chdir(data->next->arg);
		else
		{
			if (!pwd && (data->next->arg[0] == '.') && (data->next->arg[1] == '.') && (data->next->arg[2] == '\0'))
				path = global.old_pwd;
			else
			{
				if (!pwd)
					pwd = global.old_pwd;
				path = ft_strjoin2(pwd, data->next->arg);
			}
			check = chdir(path);
			if (path)
				free (path);
		}
	}
	else
		check = chdir("/Users/idabligi");
	if (check == -1)
	{
		if (data->next)
			printf("cd: %s: No such file or directory\n", data->next->arg);
		else
			perror("cd");
		return ;
	}
	printf("NEWPWD=%s\n", global.new_pwd);
	if (pwd)
	{
		if (global.new_pwd)
			free (global.new_pwd);
		global.new_pwd = getcwd(NULL, 0);
	}
	printf("NEWPWD=%s\n", global.new_pwd);
	// ft_re_env();
}

//---------------------------------------------------------------//

void	*ft_memcpy(void *dst, const char *src, int n)
{
	int	i;

	i = 0;
	if (src == dst)
		return (dst);
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

//---------------------------------------------------------------//

void	ft_run_doc(t_list *data, t_store *store)
{
	// global.gbl_doc = 1;
	// global.gbl_check_doc = 1;
	store->doc = 0;
	while (data)
	{
		if (data->tatto == 7)
		{
			store->doc++;
			ft_here_doc(data, store->doc, 0, NULL);
		}
		data = data->next;
	}
	store->doc = 0;
	// global.gbl_check_doc = 0;
}

//---------------------------------------------------------------//

int	ft_get_heredoc( int count, int fd, int check)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(count);
	join = ft_strjoin("/tmp/", itoa);
	if (check)
	{
		unlink(join);
		if ((fd = open(join, O_CREAT | O_APPEND | O_WRONLY, 0644)) < 0)
		{
			perror("Error Creating heredoc file");
			exit (1);
		}
	}
	else
		fd = open(join, O_RDONLY);
	free (join);
	return (fd);
}

//---------------------------------------------------------------//

void	ft_here_doc(t_list *data, int doc, int num, char *line)
{
	num = ft_get_heredoc(doc, 0, 1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return ;
		if (!ft_strcmp(line, data->next->arg))
		{
			free (line);
			close (num);
			return ;
		}
		write(num, line, ft_strlen(line));
		write(num, "\n", 1);
		free(line);
	}
	return ;
}

