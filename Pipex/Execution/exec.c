/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:11:35 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/14 17:21:21 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *args[] = { "ls","-a ", NULL };
    if (execve("/bin/ls", args, NULL) == -1) {
        perror("execve");
    }
    printf("This line will not be executed\n");
    return 0;
}
