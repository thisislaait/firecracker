#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * printPrompt - Displays the shell prompt.
 *
 * Description: Prints the shell prompt, indicating that the shell is ready
 * to accept user input.
 * The prompt is displayed in green color.
 *
 */
void printPrompt(void)
{
	printf(ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);
	fflush(stdout);
}
