/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:09:27 by idabligi          #+#    #+#             */
/*   Updated: 2023/03/21 11:19:37 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main() {
    char *argv[] = {"ls -l" ,"/Users/idabligi/Desktop/Minishell Testing", NULL};
    char *envp[] = {NULL};

    int status = execve("/bin/ls", argv, envp);

    if (status == -1) {
        perror("execve");
        return 1;
    }
    return 0;
}
