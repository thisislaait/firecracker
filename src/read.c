#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char* readInput() {
    char* input = NULL;
    size_t bufferSize = 0;

    ssize_t bytesRead;
    bytesRead = getline(&input, &bufferSize, stdin);

    if (bytesRead == -1) {
        if (isatty(STDIN_FILENO)) {
            write(STDOUT_FILENO, "\n", 1);
        }
        free(input);
        if (feof(stdin)) {
            printf(ANSI_COLOR_GREEN "Goodbye! Exiting the shell.\n" ANSI_COLOR_RESET);
            exit(EXIT_SUCCESS); /* Ctrl-D pressed */
        } else {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    return input;
}
