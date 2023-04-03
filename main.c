/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:24:27 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/03 16:07:07 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_separit(t_data *a)
{
    a->i = 0;
    a->tab=ft_split(a->input,' ');
    while (a->tab[a->i])
    {
        printf("%s\n",a->tab[a->i]);
        a->i++;
    }
}
void open_quote(t_data *a)
{
    a->z = 0;
    a->i = 0;
    a->k = 0;
    while (a->input[a->i])
    {
        if ((a->input[a->i] == 39 || a->input[a->i] == 34) && a->k == 0)
        {
                a->k = 1;
                a->z = 1;
            a->t = a->input[a->i];
        }
        else if ((a->input[a->i] == 39 || a->input[a->i] == 34 ) && (a->k == 1))
        {
            if (a->input[a->i] == a->t)
            {
                a->z = 0;
                a->k = 0;
            }
        }
        a->i++;
    }
    if (a->z == 1)
        printf("\e[1;31m open quotes!\n\e[0m");
    else
        ft_separit(a);
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