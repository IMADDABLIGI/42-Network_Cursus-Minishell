/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:48:24 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/15 22:03:26 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    printf("hello\n");
    printf("how are u\n");
    printf("doing\n");
    unlink("note");
    // printf("%s %s\n", av[1], av[2]);
}