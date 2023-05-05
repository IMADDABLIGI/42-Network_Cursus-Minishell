/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:12:06 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/05 16:54:02 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-------------------------------------------------------------------------------//

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*(s + i) == c)
			return (s + i);
		i++;
	}
	return (0);
}

//-------------------------------------------------------------------------------//

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	void	*potr;

	i = 0;
	potr = s;
	while (i < n)
	{
		*(unsigned char *)potr++ = '\0';
		i++;
	}
}

//-------------------------------------------------------------------------------//

void	*ft_calloc(size_t count, size_t size)
{
	void	*p1;

	p1 = malloc(count * size);
	if (!p1)
		return (0);
	ft_bzero(p1, count * size);
	return (p1);
}

//-------------------------------------------------------------------------------//

char	*ft_strjoin(char *s1, char *s2, int i, int j)
{
	char	*string;
	int		mix;

	mix = ft_strlen(s1) + ft_strlen(s2);
	string = malloc((mix + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		string[i + j] = s2[j];
		j++;
	}
	string[mix] = '\0';
	free((char *)s1);
	return (string);
}
