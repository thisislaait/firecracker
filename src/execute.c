#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 *  executeCommand - Executes a shell command.
 *  @command: The command to execute.
 *  Description: Executes a shell command by forking a new process,
 *  replacing its image with the specified command, and
 *  handling the results of the command execution.
 *
 *  Return: This function does not return a value.
 */

void executeCommand(char *command)
{
	/* Split the command into executable and arguments */
	char *executable = strtok(command, " ");
	char *arguments[10];
	pid_t pid = fork();

	int i = 0;
	int j;

	if (command == NULL)
	{
		fprintf(stderr, "Error: Unexpected end of input\n");
		exit(EXIT_FAILURE);
	}

	while (i < 9 && (arguments[i] = strtok(NULL, " ")) != NULL)
	{
		i++;
	}
	arguments[i] = NULL; /* Null-terminate the argument list */

	if (pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		/* Debugging prints */
		printf("Executable: %s\n", executable);

        for (j = 0; arguments[j] != NULL; ++j) {
            printf("Argument %d: %s\n", j, arguments[j]);
        }

		execvp(executable, arguments);

		/* If execvp fails */
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			int exitCode = WEXITSTATUS(status);
			if (exitCode != 0)

			{
				fprintf(stderr, "Command exited with code %d\n", exitCode);
			}
		}
		else
		{
			fprintf(stderr, "Command did not exit successfully\n");
		}
	}
}

