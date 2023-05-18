/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:52:56 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/18 18:01:20 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_all22(char **str, int max)
{
	max--;
	while (max >= 0)
	{
		free(str[max]);
		max--;
	}
	free(str);
	return (0);
}
/*----------------------------------------------------------------*/

char	**ft_split22(t_data *a)
{
	if (!a->input)
		return (0);
	a->tab = malloc((nbr_of_words22(a) + 1) * (sizeof(char *)));
	if (!a->tab)
		ft_abort(1);
	return (ft_return22(a));
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
		ft_abort(1);
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
		ft_abort(1);
	while (y < i)
	{
		f[y] = s1[y];
		y++;
	}
	f[y] = '\0';
	return (f);
}
