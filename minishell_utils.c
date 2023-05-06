/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/06 12:38:18 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strcmp2(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

//---------------------------------------------------------------//

int	ft_get_heredoc(t_list *data, int count, int fd, int check)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(count);
	join = ft_strjoin("/tmp/", itoa);
    free (itoa);
    if (check)
    {
        unlink(join);
        if ((fd = open(join, O_CREAT | O_APPEND | O_RDWR, 0644)) < 0)
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
	num = ft_get_heredoc(data, doc, 0, 1);
	
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp2(line, data->next->arg) == 0)
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

