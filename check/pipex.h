/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:13:53 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/11 01:53:04 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_check_cmd(char *cmd);
int		ft_check_path(char *path);
void	*ft_memcpy(void *dst, const void *src, int n);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
char	**free_all(char **ptr, size_t i);

#endif