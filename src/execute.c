#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * env_builtin - Implementation of the
 * 'env' built in command.
*/
void env_builtin(void)
{
	char **env;
	/* Print each environment variable */
	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
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
	if (strcmp(command, "env") == 0)
	{
		env_builtin();
	}
	else
	{
		char *argv[20]; /* Adjust the array size as needed */
		pid_t pid;

		splitCommand(command, argv, 20);

		if (strchr(argv[0], '/') != NULL)
		{
			/*The command includes a path, execute directly*/
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
			}
		}
		else
		{
			/*Search for the command in PATH*/
			searchAndExecute(argv[0], argv);
		}
	}
}

