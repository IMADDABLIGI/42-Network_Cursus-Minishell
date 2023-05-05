/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:47 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/05 14:12:21 by idabligi         ###   ########.fr       */
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