/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/08 17:40:45 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_separit(t_data *a)
{
    // ft_split(a);
    if (!ft_split(a))
        return(printf("problem in malloc !\n"));
    a->i = 0;
    while (a->tab[a->i])
    {
        printf("%s\n",a->tab[a->i]);
        a->i++;
    }
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
        ft_separit(a);
}
// void check_parsing(t_data *a)
// {
//     a->k = 0;
//     a->lock = 0;   
//     a->z = 0;
// 	a->lock1 = 0;
// 	a->t = '\0';
//        while (a->input[a->k])
//        {
//             if(a->input[a->k] == 39 || a->input[a->k] == 34)
//             {
//                 if (!a->lock1)
//                 {
//                     a->t = a->input[a->k];
//                     a->lock1 = 1;
//                 }
//                 else if (a->input[a->k] == a->t && a->lock1)
//                 {
//                     a->t = a->input[a->k];
//                     a->lock1 = 0;
//                 } 
//             }
//             else if ((a->input[a->k] == '<' || a->input[a->k] == '>' || a->input[a->k] == '|' ) && !a->lock1)
//             {
//                 if ((a->input[a->k] == '<' && a->input[a->k+1] == '<') || (a->input[a->k] == '>' && a->input[a->k+1] == '>'))
//                     a->k+=1;
//                 if (!a->z)
//                     a->z=1;
//                 else if (a->z)
//                     return(1);
//             }
//             a->k++;
//        }   
//        return(0);
// }
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