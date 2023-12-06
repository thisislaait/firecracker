#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void printPrompt() {
    printf(ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);
    fflush(stdout);
}
