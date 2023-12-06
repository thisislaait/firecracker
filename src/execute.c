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
    char *token;
    char *argv[20];  /*Adjust the array size as needed*/
    pid_t pid;

    int i = 0;
    int j;

    if (command == NULL)
    {
        fprintf(stderr, "Error: Unexpected end of input\n");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the command */
    token = strtok(command, " ");
    while (token != NULL && i < 19)  /*Adjust the limit as needed*/
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL; /* Null-terminate the argument list */

    pid = fork();

    if (pid == -1)
    {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        execvp(argv[0], argv);

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

}

