/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rijal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:24:27 by hznagui           #+#    #+#             */
/*   Updated: 2023/03/31 13:24:27 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main() {
    char *input;
    
    input = readline("minishell :");
    
    printf("You entered: %s\n", input);
    
    free(input);
    return 0;
}