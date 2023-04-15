/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:00:44 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/07 02:47:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_callstg(char **ptr, char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			i++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	ptr = malloc((count + 1) * sizeof(char *));
	if (!ptr)
	{
		free(ptr);
		return (0);
	}
	ptr[count] = 0;
	return (ptr);
}

static size_t	len_string(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*wrt_stg(char const *s, char c)
{
	size_t	len_s;
	char	*pptr;

	len_s = len_string(s, c);
	pptr = malloc((len_s + 1) * sizeof(char));
	if (!pptr)
	{
		free(pptr);
		return (0);
	}
	ft_memcpy(pptr, s, len_s);
	pptr[len_s] = '\0';
	return (pptr);
}

static char	**free_all(char **ptr, size_t i)
{
	while (i--)
		free(ptr[i]);
	free(ptr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;

	if (!s)
		return (0);
	ptr = NULL;
	ptr = ft_callstg(ptr, s, c);
	if (!ptr)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			ptr[i++] = wrt_stg(s, c);
			if (!ptr[i - 1])
				return (free_all(ptr, i));
		}
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (ptr);
}