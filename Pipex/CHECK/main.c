/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:44:41 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/06 02:05:35 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
    if (ft_check_cmd("ls -al") == 0)
        printf("HAD LCOMMAND KAYNA\n");//You can try every CMD you like.
    else
        printf("LA WALLO HAD LCOMMAND GA3MA KAYNA\n");//if a valid CMD wouldn't have been found, that means u have to make it ur own and not by execve standard function.

    //-------------------------------------------------//
    
    if (ft_check_path("/Users/HOUDAIFA_ZAMEL/Desktop/Minishell"))//Read the path again.
        printf("HAD PATH KAYN\n");
    else
        printf("LA WALLO HAD PATH GA3MA KAYN\n");
}
