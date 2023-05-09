/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:12:06 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/09 17:25:06 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlengl(s);
	while (i <= len)
	{
		if (*(s + i) == c)
		{
			return ((char *) s + i);
		}
		i++;
	}
	return (0);
}

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

void	*ft_calloc(size_t count, size_t size)
{
	void	*p1;

	p1 = malloc(count * size);
	if (!p1)
		return (0);
	ft_bzero(p1, count * size);
	return (p1);
}

size_t	ft_strlengl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoingl(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;
	int		mix;

	mix = ft_strlengl(s1) + ft_strlengl(s2);
	string = malloc((mix + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		string[i + j] = s2[j];
		j++;
	}
	string[mix] = '\0';
	free((char *)s1);
	return (string);
}
