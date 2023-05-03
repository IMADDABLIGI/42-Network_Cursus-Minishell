/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/03 10:13:08 by hznagui          ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
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
		return (0);
	ft_memcpy(string, s1, lens1);
	string[lens1] = '/';
	ft_memcpy(string + lens1 + 1, s2, lens2);
	string[mix] = '\0';
	return (string);
}

//---------------------------------------------------------------//

// char	*ft_strdup(const char *s1)
// {
// 	size_t	i;
// 	size_t	size;
// 	char	*ptr;

// 	i = 0;
// 	size = ft_strlen(s1);
// 	ptr = (char *)malloc((size + 1) * sizeof(char));
// 	if (!ptr)
// 		return (0);
// 	ft_memcpy(ptr, s1, size);
// 	ptr[size] = '\0';
// 	return (ptr);
// }