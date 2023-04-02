/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:24:27 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/02 16:38:23 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void open_quote(t_data *a)
{
    a->z = 0;
    a->i = 0;
    a->k = 0;
    
    while (a->input[a->i])
    {
        if (a->input[a->i] == 39 && a->k == 0)
        {
            a->z = 1;
            a->k = 1;
        }
        else if (a->input[a->i] == 39 && a->k == 1)
        {
            a->z = 0;
            a->k = 0;
        }
        a->i++;
    }
    if (a->z == 1)
        printf("\e[1;31m open quotes!\n \e[0m");   
}

int main() {
    
    t_data a;
    while (1)
    {
        a.input = readline("\e[2;34mMINISHELL$ \e[0m");
        printf ("%s",a.input);
        // open_quote(&a);
        if (a.input[0])
            add_history(a.input);
        free(a.input);
        // a.input = NULL ;
        // rl_replace_line();
        // printf("%s\n", a.input);
    }
    return 0;
}