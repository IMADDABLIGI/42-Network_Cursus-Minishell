/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:36:15 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/07 16:46:28 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpath(char *cmd)
{
	int		i;
	char	**p_cmd;
	char	**s_cmd;

	i = 0;
	p_cmd = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (p_cmd[i])
	{
		if (access(ft_strjoin(p_cmd[i], s_cmd[0]), F_OK) == 0)
			return (ft_strjoin(p_cmd[i], s_cmd[0]));
		i++;
	}
	return (NULL);
}

char	**ft_arg(char **arg, char *path)
{
	int		i;
	char	**n_arg;

	i = 0;
	while (arg[i])
		i++;
	printf("%d\n", i);
	n_arg = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (arg[i] != NULL)
	{
		n_arg[i] = arg[i];
		i++;
	}
	n_arg[i] = path;
	n_arg[i + 1] = NULL;
	return (n_arg);
}
