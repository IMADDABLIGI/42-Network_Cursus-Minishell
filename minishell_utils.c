/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/09 14:38:07 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glb global;

//---------------------------------------------------------------//

void	ft_re_env()
{
	global.old_pwd = ft_strjoin("OLDPWD=", global.old_pwd);
	printf("%s\n", global.old_pwd);
}

//---------------------------------------------------------------//

void	ft_cd(t_list *data, int check, char *path, char *pwd)
{
	// global.old_pwd = getcwd(NULL,0);
	if (data->next)
	{
		if ((data->next->tatto == 5) || (data->next->tatto == 6) || (data->next->tatto == 7)
			|| (data->next->tatto == 8) || (data->next->tatto == 4))
			return ;
		if ((data->next->arg[0] == '~') && (data->next->arg[1] == '\0'))
			check = chdir("/Users/idabligi");
		else if (data->next->arg[0] == '/')
			check = chdir(data->next->arg);
		else
		{
			pwd = getcwd(NULL,0);
			path = ft_strjoin2(pwd, data->next->arg);
			check = chdir(path);
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
	// global.new_pwd = getcwd(NULL, 0);
	// printf("PWD=%s\n", global.new_pwd);
	// printf("OLDPWD=%s\n", global.old_pwd);
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
	global.gbl_doc = 1;
	global.gbl_check_doc = 1;
	while (data)
	{
		if (data->tatto == 7)
		{
			store->doc++;
			ft_here_doc(data, store->doc, 0, NULL);
		}
		data = data->next;
	}
	global.gbl_check_doc = 0;
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

int	ft_here_doc(t_list *data, int doc, int num, char *line)
{
	num = ft_get_heredoc(doc, 0, 1);
	while (global.gbl_doc)
	{
		line = readline("> ");
		if (line == NULL)
			return (1);
		if (!ft_strcmp(line, data->next->arg))
		{
			free (line);
			close (num);
			return (num);
		}
		write(num, line, ft_strlen(line));
		write(num, "\n", 1);
		free(line);
	}
	return (0);
}

