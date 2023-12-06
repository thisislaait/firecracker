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
 * @argv: The array of arguments.
 */
static void executeChild(char *argv[])
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
	} else
	{
		fprintf(stderr, "Command did not exit successfully\n");
	}
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
	} else if (pid == 0)
	{
		/* Child process */
		executeChild(argv);
	} else
	{
		/* Parent process */
		executeParent(pid);
	}
}

