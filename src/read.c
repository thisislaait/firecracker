#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * readInput - Reads a line of input from the user.
 *
 * Return: Allocated string containing the user's input.
 *
 * Description: Returned string is null-terminated
 * and does not contain the newline character.
 * If an error occurs or if the user enters an empty line,
 * the function returns NULL.
 *
 */
char *readInput(void)
{
	char *input = NULL;
	size_t bufferSize = 0;
	ssize_t bytesRead;

	bytesRead = getline(&input, &bufferSize, stdin);
	if (bytesRead == -1)

	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		free(input);
		if (feof(stdin))
		{
			printf(ANSI_COLOR_GREEN "Goodbye! Exiting the shell.\n"
					ANSI_COLOR_RESET);
			exit(EXIT_SUCCESS); /* Ctrl-D pressed */
		} else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}
	return (input);
}
