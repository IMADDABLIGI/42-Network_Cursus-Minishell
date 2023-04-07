/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:36:15 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/07 02:48:17 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpath(char *cmd)
{
	int		i;
	char	*path;
	char	**p_cmd;
	char	**s_cmd;

	i = 0;
	path = getenv("PATH");
	p_cmd = ft_split(path, ':');
	s_cmd = ft_split(cmd, ' ');
	while (p_cmd[i])
	{
		if (access(ft_strjoin(p_cmd[i], s_cmd[0]), F_OK) == 0)
			return (ft_strjoin(p_cmd[i], s_cmd[0]));
		i++;
	}
	return (NULL);
}
