/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:13:53 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/04 01:06:40 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, int n);
char	**ft_split(char const *s, char c);
void	ft_write_error(char *str);
int		ft_strlen(const char *s);
void	ft_write_error2(char *str);
char	*ft_access(char **p_cmd, char *s_cmd);
void	ft_firstcmd(char *infile, char *cmd, int *fd);
void	ft_midcmd(char *cmd, int *fd);
void	ft_lastcmd(char *infile, char *cmd, int *fd);

#endif