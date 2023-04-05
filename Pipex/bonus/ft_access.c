/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:26:09 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/03 23:52:29 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_access(char **p_cmd, char *s_cmd)
{
	int	check;
	int i;

	i = 0;
	while (p_cmd[i])
	{
		check = access(ft_strjoin(p_cmd[i], s_cmd), F_OK);
		if (check == 0)
			return (ft_strjoin(p_cmd[i], s_cmd));
		i++;
	}
	write(1, "command not found : ", 20);
	write(1, s_cmd, ft_strlen(s_cmd));
	return (NULL);
}
