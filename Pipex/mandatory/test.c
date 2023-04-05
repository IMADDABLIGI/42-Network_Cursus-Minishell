/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/03 17:07:43 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(fd[1]); // Close the write end of the pipe

        int n = 0;
        char *commands[100]; // Assume we'll have no more than 100 commands
        char *token;

        // Read commands from the pipe
        while (read(fd[0], buffer, BUFFER_SIZE) != 0) {
            token = strtok(buffer, " \n");
            while (token != NULL) {
                commands[n] = token;
                n++;
                token = strtok(NULL, " \n");
            }
        }

        // Execute the commands
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                // First command, no need to pipe output
                execve(commands[i], commands, NULL);
            } else {
                // Not the first command, pipe output from previous command
                int pipefd[2];
                if (pipe(pipefd) == -1) {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                pid_t pid = fork();

                if (pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0) {
                    // Child process
                    close(pipefd[0]); // Close the read end of the pipe
                    if (dup2(fd[0], STDIN_FILENO) == -1) {
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                    execve(commands[i], commands, NULL);
                } else {
                    // Parent process
                    close(fd[0]); // Close the read end of the pipe
                    close(pipefd[1]); // Close the write end of the pipe
                    fd[0] = pipefd[0]; // Save the read end of the pipe for the next command
                }
            }
        }

        close(fd[0]); // Close the read end of the pipe
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(fd[0]); // Close the read end of the pipe

        // Read commands from the user and write them to the pipe
        while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            write(fd[1], buffer, strlen(buffer));
        }

        close(fd[1]); // Close the write end of the pipe
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}