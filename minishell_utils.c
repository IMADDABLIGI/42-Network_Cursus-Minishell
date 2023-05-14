/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 18:30:14 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_run_doc(t_list *data, t_store *store, t_data *a)
{
	store->doc = 0;
	g_global.doc = 1;
	while (data)
	{
		if (data->tatto == 7)
		{
			store->doc++;
			a->line = NULL;
			ft_here_doc(data, store->doc, 0, a);
			if (!g_global.doc)
			{
				dup2(g_global.save, STDIN_FILENO);
				close(g_global.save);
				return (0);
			}
		}
		data = data->next;
	}
	store->doc = 0;
	return (1);
}

//---------------------------------------------------------------//

int	ft_get_heredoc(int count, int fd, int check)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(count);
	join = ft_strjoin("/tmp/", itoa, 0);
	if (check)
	{
		unlink(join);
		fd = open(join, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("Error Creating heredoc file");
			exit(1);
		}
	}
	else
		fd = open(join, O_RDONLY);
	free(join);
	return (fd);
}

//---------------------------------------------------------------//

void	ft_handlec(int sig)
{
	(void)sig;
	g_global.save = dup(STDIN_FILENO);
	g_global.doc = 0;
	g_global.status = 1;
	rl_replace_line("", 0);
	close(0);
}

//---------------------------------------------------------------//

void	ft_here_doc(t_list *data, int doc, int num, t_data *a)
{
	num = ft_get_heredoc(doc, 0, 1);
	while (g_global.doc)
	{
		signal(SIGINT, ft_handlec);
		a->line = readline("> ");
		if (a->line == NULL)
			return ;
		if (!ft_strcmp(a->line, data->next->arg))
		{
			close(num);
			free(a->line);
			g_global.status = 0;
			return ;
		}
		a->line = expand_her(a);
		write(num, a->line, ft_strlen(a->line));
		write(num, "\n", 1);
		free(a->line);
	}
}
