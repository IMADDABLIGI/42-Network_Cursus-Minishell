/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/10 01:24:10 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_length(t_data *a)
{
    size_t x;
    size_t len;
    int lock;
    
    lock = 0;
    x = 0;
    len=0;
    while (a->tab[a->i][x])
    {
        if ((a->tab[a->i][x] == 39 || a->tab[a->i][x] == 34) && !lock)
        {
            lock = 1;
            a->t = a->tab[a->i][x];
        }
        else if (a->t == a->tab[a->i][x] && lock)
        {
             lock = 0;
             a->t = '\0';
        }
        else
            len++;
        x++;
    }
    return(len);
}
char *str(t_data *a)
{
    char *p;
    size_t x;
    int lock;
    
    p = malloc(sizeof(char)*ft_length(a));
    a->k=0;
    lock = 0;
    x = 0;
    while (a->tab[a->i][x])
    {
        if ((a->tab[a->i][x] == 39 || a->tab[a->i][x] == 34) && !lock)
        {
            lock = 1;
            a->t = a->tab[a->i][x];
        }
        else if (a->t == a->tab[a->i][x] && lock)
        {
             lock = 0;
             a->t = '\0';
        }
        else
        {
            p[a->k]=a->tab[a->i][x];
        a->k++;
        }
        x++;
    }
    p[a->k]='\0';
    return(p);
}
void create_linked(t_data *a)
{
    t_arg *o;
    
    a->i=0;
    a->p=NULL;
    while (a->tab[a->i])
    {
        o = ft_lstnew(a);
        if (!o)
            ft_lstclear(&a->p); 
        ft_lstadd_back(&a->p,o);
        a->i++;
    }
    // o = a->p;
    // while (o)
    // {
    //     printf("%s\n",o->arg);
    //    o = o->next;
    // }
}
int ft_separit(t_data *a)
{
    if (!ft_split(a))
        return(printf("problem in malloc !\n"));
    a->i = 0;
    create_linked(a);
    return(0);
}
void open_quote(t_data *a)
{
    a->z = 0;
    a->i = 0;
    a->lock = 0;
    a->t = '\0';
    while (a->input[a->i])
    {
        if ((a->input[a->i] == 39 || a->input[a->i] == 34) && a->lock == 0)
        {
                a->lock = 1;
                a->z = 1;
            a->t = a->input[a->i];
        }
        else if ((a->input[a->i] == 39 || a->input[a->i] == 34 ) && (a->lock == 1))
        {
            if (a->input[a->i] == a->t)
            {
                a->z = 0;
                a->lock = 0;
            }
        }
        a->i++;
    }
    if (a->z == 1)
        printf("\e[1;31m open quotes!\n\e[0m");
    else
    {
        if(!ft_separit(a))
            free_all(a->tab,a->length);
        ft_lstclear(&a->p);
    }
}
int main() {
    t_data a;
    while (1)
    {
        a.input = readline("MINISHELL>> ");
        if (*(a.input))
            add_history(a.input);
        open_quote(&a);
        free(a.input);
    }
    return 0;
}