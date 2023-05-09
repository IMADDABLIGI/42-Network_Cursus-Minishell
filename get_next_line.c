/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:12:53 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/09 17:23:39 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_save(int fd, char *save)
{
	char	*buff;
	int		readvl;

	if (!save)
		save = ft_calloc(1, 1);
	if (!save)
		return (NULL);
	buff = ft_calloc((1 + 1), sizeof(char));
	readvl = 1;
	while (readvl > 0)
	{
		readvl = read(fd, buff, 1);
		if (readvl == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readvl] = 0;
		save = ft_strjoin(save, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (save);
}

char	*ft_line(char *save)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	if (!save[count])
		return (NULL);
	while (save[count] != '\0' && save[count] != '\n')
		count++;
	if (save[count] == '\n')
		count++;
	line = ft_calloc((count + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < count)
	{
		line[i] = save[i];
		i++;
	}
	return (line);
}

char	*ft_next(char *save)
{
	char	*next_save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strchr(save, '\n') == 0)
		return (free(save), NULL);
	while (save[i] != '\n')
	i++;
	i += 1;
	while (save[i + j] != '\0')
		j++;
	next_save = ft_calloc((j + 1), sizeof(char));
	if (!next_save)
		return (NULL);
	j = 0;
	while (save[i + j] != '\0')
	{
		next_save[j] = save[i + j];
		j++;
	}
	return (free(save), next_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	save = ft_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_line(save);
	save = ft_next(save);
	return (line);
}
