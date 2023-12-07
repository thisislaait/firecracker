#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "shell.h"

/**
 * initializeShell - Initializes the shell environment.
 *
 * Description: Execution to set up the environment.
 * Function is left empty if no initialization.
 *
 */
void initializeShell(void)
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag & = ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
