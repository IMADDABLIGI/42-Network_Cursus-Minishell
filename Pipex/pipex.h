/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:13:53 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/01 16:53:39 by idabligi         ###   ########.fr       */
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
void	ft_firstcmd(char *infile, char *cmd);
void	ft_write_error(char *str);
char	*ft_access(char **p_cmd, char *s_cmd);
void	ft_secoundcmd(char *infile, char *cmd);

#endif