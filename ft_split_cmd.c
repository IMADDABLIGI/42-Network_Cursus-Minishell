/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:20:00 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 09:22:00 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_callstg(char **ptr, char *s, char c)
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
		ft_abort(1);
	ptr[count] = 0;
	return (ptr);
}

static size_t	len_string(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*wrt_stg(char *s, char c, char *cmd)
{
	size_t	len_s;
	char	*pptr;
	int		cd;
	int		i;

	i = 0;
	len_s = len_string(s, c);
	cd = ft_strlen(cmd) + 1;
	pptr = malloc((len_s + cd + 1) * sizeof(char));
	if (!pptr)
		return (free(pptr), NULL);
	ft_memcpy(pptr, s, len_s);
	pptr[len_s] = '/';
	len_s++;
	while (i != cd)
	{
		pptr[len_s] = cmd[i];
		i++;
		len_s++;
	}
	pptr[len_s] = '\0';
	return (pptr);
}

static char	**free_all(char **ptr, size_t i)
{
	while (i--)
		free(ptr[i]);
	free(ptr);
	ft_abort(1);
	return (0);
}

char	**ft_split_cmd(char *s, char c, char *cmd)
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
			ptr[i++] = wrt_stg(s, c, cmd);
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
