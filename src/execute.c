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
static void splitCommand(char *command, char *argv[], int maxArgs)
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
static void executeChild(char *path)
{
	execvp(path, path, NULL);
	/* If execvp fails */
	perror("Error executing command");
	exit(EXIT_FAILURE);
}

/**
 * executeParent - Waits for the child process to complete.
 * @pid: The process ID of the child.
 */
static void executeParent(pid_t pid)
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
 * searchAndExecute - Searches for the executable in the PATH.
 * @command: The command to execute.
*/
static void searchAndExecute(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char *fullPath;
	int commandLen = strlen(command);

	while (token != NULL)
	{
		fullPath = malloc(strlen(token) + commandLen + 2);
		if (fullPath ==NULL)
		{
			perror("Malloc failed");
			exit(EXIT_FAILURE);
		}

		strcpy(fullPath, token);
		strcat(fullPath, "/");
		strcat(fullPath, command);

		if (access(fullPath, X_OK) == 0)
		{
			executeChild(fullPath);
		}

		free(fullPath);
		token = strtok(NULL, ":");
	}

	fprintf(stderr, "Command not found: %s\n", command);
	exit(EXIT_FAILURE);
}

/**
 * executeCommand - Executes a shell command.
 * @command: The command to execute.
 * Description: Executes a shell command by forking a new process,
 * replacing its image with the specified command, and
 * handling the results of the command execution.
 *
 * Return: This function does not return a value.
 */
void executeCommand(char *command)
{
	char *argv[20]; /* Adjust the array size as needed */
	pid_t pid;

	splitCommand(command, argv, 20);

	pid = fork();
	if (pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		searchAndExecute(argv[0]);
	}
	else
	{
		/* Parent process */
		executeParent(pid);
	}
}

