/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:24:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/03 17:41:47 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc,char **argv) {
    int i=1;
 while (argv[i])
 {
    printf("<%s>\n",argv[i]);
    i++;
 }
    return 0;
}




