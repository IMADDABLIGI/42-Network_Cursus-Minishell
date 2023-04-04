/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/03 16:06:13 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

typedef struct data 
{
    char *input;
    char **tab;
    int z;
    int i;
    int k;
    char t;
}t_data ;
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
#endif
