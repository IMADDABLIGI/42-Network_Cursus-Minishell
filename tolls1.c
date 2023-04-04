/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:52:56 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/03 17:07:24 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	nbr_of_words(char *s, char c)
{
	size_t	k;
	size_t	h;
	size_t	l;

	k = 0;
	h = 0;
	l = 0;
	while (s[k])
	{
		if (s[k] != c && h == 0)
		{
			l++;
			h = 1;
		}
		else if (s[k] == c && h == 1)
		{
			h = 0;
		}
		k++;
	}
	return (l);
}

static char	**free_all(char **str, size_t max)
{
	int	i;

	i = max;
	while (i >= 0)
		free(str[i--]);
	free (str);
	return (0);
}

static char	**ft_return(char *s, char c, char **p)
{
	size_t	e;
	size_t	u;
	size_t	a;

	u = 0;
	a = 0;
	while (u < nbr_of_words((char *)s, c))
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		e = a;
		while (s[e] != c && s[e] != '\0')
			e++;
		p[u] = ft_substr((char *)s, a, e - a);
		if (!p[u])
		{
			return (free_all(p, u));
		}
		u++;
		a = e;
	}
	p[u] = NULL;
	return (p);
}
char	**ft_split(char *s, char c)
{
	char	**p;

	if (!s)
		return (0);
	p = malloc((nbr_of_words((char *)s, c) + 1) * (sizeof(char *)));
	if (!p)
		return (0);
	return (ft_return((char *)s, c, p));
}
/*----------------------------------------------------------------*/
static size_t	leakskiller(char *s, unsigned int start, size_t len)
{
	if (ft_strlen(s + start) >= len)
	{
		return (len);
	}
	else
	{
		return (ft_strlen(s + start));
	}
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	o;
	char	*p;

	if (!s)
		return (0);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	p = malloc((leakskiller(s, start, len) + 1) * sizeof(char));
	if (!p)
		return (0);
	o = 0;
	while (o < len && s[start + o])
	{
		p[o] = s[start + o];
		o++;
	}
	p[o] = '\0';
	return (p);
}
/*----------------------------------------------------------------*/
char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	y;
	char	*f;

	y = 0;
	i = ft_strlen(s1);
	f = malloc((i + 1) * sizeof(char));
	if (!f)
		return (0);
	while (y < i)
	{
		f[y] = s1[y];
		y++;
	}
	f[y] = '\0';
	return (f);
}
/*----------------------------------------------------------------*/
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}