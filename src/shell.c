#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int main(void) {
    char *input;
    initializeShell();

    while (1) {
        printPrompt();
        input = readInput();

        if (feof(stdin)) {
            free(input);
            printf(ANSI_COLOR_GREEN "Goodbye! Exiting the shell.\n" ANSI_COLOR_RESET);
            break;
        }

        if (input[0] != '\n') {
            input[strlen(input) - 1] = '\0';

            if (strcmp(input, "exit") == 0) {
                free(input);
                printf(ANSI_COLOR_GREEN "Goodbye! Exiting the shell.\n" ANSI_COLOR_RESET);
                break;
            } else {
                executeCommand(input);
            }
        }

        free(input);
    }

    return 0;
}

