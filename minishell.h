/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/09 17:56:55 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

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
}t_data ;
/*
command 1
path_to_file */
t_arg	*ft_lstnew(char *content);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
t_arg	*ft_lstclear(t_arg **lst);
char	**ft_split(t_data *a);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**free_all(char **str, size_t max);
#endif
