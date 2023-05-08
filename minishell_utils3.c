/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:08:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/08 15:39:52 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

static int	ln_n(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

//---------------------------------------------------------------------------//

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*ptr;

	i = 0;
	nb = n;
	n = ln_n(nb);
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		ft_abort(1);
	if (nb == 0)
		ptr[0] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		ptr[n - i - 1] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	ptr[n] = '\0';
	return (ptr);
}

//---------------------------------------------------------------------------//

static char	*ft_return(char *p, char  *s1, char *s2)
{
	size_t	y;
	size_t	a;

	a = 0;
	y = 0;
	while (y < ft_strlen(s1))
	{
		p[y] = s1[y];
		y++;
	}
	while (a <= ft_strlen(s2))
	{
		p[y + a] = s2[a];
		a++;
	}
	return (p);
}

//---------------------------------------------------------------------------//

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		ft_abort(1);
	return (ft_return(p, s1, s2));
}

//---------------------------------------------------------------------------//

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*string;
	int		lens1;
	int		lens2;
	int		mix;

	if (!s1 && !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	mix = ft_strlen(s1) + ft_strlen(s2) + 1;
	string = malloc((mix + 1) * sizeof(char));
	if (!string)
		ft_abort(1);
	ft_memcpy(string, s1, lens1);
	string[lens1] = '/';
	ft_memcpy(string + lens1 + 1, s2, lens2);
	string[mix] = '\0';
	return (string);
}

