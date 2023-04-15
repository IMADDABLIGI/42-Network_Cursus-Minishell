/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/06 23:21:38 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	int				rst;

	i = 0;
	rst = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		rst = rst * 10 + str[i++] - '0';
	return ((int)rst * sign);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, int n)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int	lens1;
	int	lens2;
	int	mix;

	if (!s1 && !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	mix = ft_strlen(s1) + ft_strlen(s2) + 1;
	string = malloc((mix + 1) * sizeof(char));
	if (!string)
		return (0);
	ft_memcpy(string, s1, lens1);
	string[lens1] = '/';
	ft_memcpy(string + lens1 + 1, s2, lens2);
	string[mix] = '\0';
	return (string);
}
