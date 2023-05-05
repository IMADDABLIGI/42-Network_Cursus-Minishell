/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/05 20:51:25 by idabligi         ###   ########.fr       */
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
	while (s1[i] != '\n' || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

//---------------------------------------------------------------//

int	ft_here_doc(t_list *data, int num, char *line)
{
	printf("HNA RAH KAYN HEREDOC\n");
	unlink("heredoc");
	if ((num = open("heredoc", O_CREAT | O_APPEND | O_RDWR, 0644)) < 0)
	{
		perror("Error Creating heredoc file");
		return (0);
	}
	printf("%d\n", num);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(1);
		write(num, line, ft_strlen(line));
		if (ft_strcmp2(line, data->next->arg) == 0)
        {
            free (line);
            close (num);
			return (num);
        }

		free(line);
	}
	return (0);
}