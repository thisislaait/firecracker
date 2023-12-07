#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * splitCommand - Tokenizes the command into executable and arguments.
 * @command: The command to split.
 * @argv: The array to store the tokens.
 * @maxArgs: The maximum number of arguments.
 */
void splitCommand(char *command, char *argv[], int maxArgs)
{
	char *token;
	int i = 0;

	if (command == NULL)
	{
		fprintf(stderr, "Error: Unexpected end of input\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(command, " ");
	while (token != NULL && i < maxArgs - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL; /* Null-terminate the argument list */
}

/**
 * executeChild - Executes the command in the child process.
 * @full_path: The full path to the executable.
 * @argv: The array of arguments.
 */
void executeChild(char *argv[])
{
	execvp(argv[0], argv);
	/* If execvp fails */
	perror("Error executing command");
	exit(EXIT_FAILURE);
}

/**
 * executeParent - Waits for the child process to complete.
 * @pid: The process ID of the child.
 */
void executeParent(pid_t pid)
{
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

/**
 * searchAndExecute - Search for the command in the PATH and execute it.
 * @command: The command to execute.
 * @argv: The array of arguments.
 */
void searchAndExecute(char *command, char *argv[])
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	pid_t pid;

	while (dir != NULL)
	{
		char full_path[256];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			/*Found the executable in the current directory */
			pid = fork();
			if (pid == -1)
			{
				perror("Error forking process");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				/* Child process */
				executeChild(argv);
			}
			else
			{
				/* Parent process */
				executeParent(pid);
				free(path_copy);
				return;
			}
		}
		dir = strtok(NULL, ":");
	}
	/*If the command is not found in any directory*/
	fprintf(stderr, "Command not found: %s\n", command);
	free(path_copy);
}
