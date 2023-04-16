/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/16 17:21:42 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include<signal.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct arg
{
    char *arg;
    int tatto;
    struct arg *next;
}t_arg;

typedef struct data 
{
    char *input;
    char **tab;
    int z;
    int lock;
    size_t length;
    int lock1;
    size_t k;
    char t;
    size_t i;
    t_arg *p;
    t_arg *tmp;
}t_data ;
/*
command 1
path_to_file */

/*parsing function*/
t_arg	*ft_lstnew(t_data *a);
t_arg	*ft_lstclear(t_arg **lst);
void tato(t_data *a);
int ft_check_path(char *path);
char *str(t_data *a,int *tatto);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
char	**ft_split22(t_data *a);
char	**free_all22(char **str, int max);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, int n);
int	ft_check_cmd(char *cmd);
char	**ft_split(char *s, char c);
char	**free_all(char **ptr, size_t i);
#endif
