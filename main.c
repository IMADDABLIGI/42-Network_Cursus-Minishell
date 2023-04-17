/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/17 00:59:33 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1,char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}
int parse_check(t_data *a)
{
    a->tmp = a->p;
    if (a->tmp->tatto == 4)
        {
                printf("parse error \n");
                return(1);
        }
    while (a->tmp)
    {
        if (a->tmp->tatto != 0 && !a->tmp->next)
        {
                printf("parse error \n");
                return(1);
        }
        if (a->tmp->tatto != 0 && a->tmp->tatto != 4 && a->tmp->next->tatto != 0)
            {
                printf("parse error \n");
                return(1);
            }
        a->tmp = a->tmp->next;
    }
    return(0);
}
void tato(t_data *a)
{
    a->tmp = a->p;
    while (a->tmp)
    {
        if (a->tmp->tatto == 0)
        {
            a->tmp->tatto = 1;
            a->tmp = a->tmp->next;
            while (a->tmp && a->tmp->tatto == 0)
            {
                a->tmp->tatto = 2;
                a->tmp = a->tmp->next;
            }
        }
        else if (a->tmp->tatto != 4)
        {
            a->tmp = a->tmp->next;
            if (a->tmp->tatto == 0)
                a->tmp->tatto = 2;
            a->tmp = a->tmp->next;
        }
        else
            a->tmp = a->tmp->next;
    }
}

void check_tato(t_data *a,int *tatto)
{
    if (!ft_strcmp(a->tab[a->i],">>"))
        *tatto = 8;
    else if (!ft_strcmp(a->tab[a->i],"<<"))
        *tatto = 7;
    else if (!ft_strcmp(a->tab[a->i],"<"))
        *tatto = 5;
    else if (!ft_strcmp(a->tab[a->i],">"))
        *tatto = 6;
    else if (!ft_strcmp(a->tab[a->i],"|"))
        *tatto = 4;     
}
size_t ft_length(t_data *a,int *tatto)
{
    size_t x;
    size_t len;
    int lock;
    
    lock = 0;
    x = 0;
    len = 0;
    check_tato(a,tatto);
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
char *str(t_data *a,int *tatto)
{
    char *p;
    size_t x;
    int lock;
    
    p = malloc(sizeof(char)*ft_length(a,tatto));
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
	t_store store;
    
    a->i=0;
    a->p=NULL;
    while (a->tab[a->i])
    {
        a->tmp = ft_lstnew(a);
        if (!a->tmp)
            ft_lstclear(&a->p); 
        ft_lstadd_back(&a->p,a->tmp);
        a->i++;
    }
    if (parse_check(a))
        return;
    tato(a);
    a->tmp=a->p;
    ft_check_arg(a->tmp, &store);
	ft_execution(a->tmp, &store);
    // o = a->p;
    // while (o)
    // {
    //     printf("%d\t",o->tatto);
    //    o = o->next;
    // }
    // printf("\n");
}
int ft_separit(t_data *a)
{
    if (!ft_split22(a))
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
        if (!ft_separit(a))
            free_all22(a->tab,a->length);
        ft_lstclear(&a->p);
    }
}
// void test(int y)
// {
//     (void)y;
//     printf("salam\n");
// }
int main() {
    t_data a;
    while (1)
    {
        a.input = readline("MINISHELL>> ");
        if (*(a.input))
            add_history(a.input);
        open_quote(&a);
        usleep(1000);
        free(a.input);
    }
    return 0;
}