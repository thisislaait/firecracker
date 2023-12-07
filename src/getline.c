#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * readInput - Reads a line from standard input.
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
    static char buffer[BUFFER_SIZE];
    static int buffer_index = 0;
    static int buffer_size = 0;
    
    char *line = NULL;
    int line_index = 0;
    char c;
    
    while (1)
    {
        /* Refill the buffer if it's empty */
        if (buffer_index == buffer_size)
        {
            buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (buffer_size <= 0)
            {
                /* Error or end of input */
                if (line_index == 0)
                    return NULL; /* No input received */
                break;
            }
            buffer_index = 0;
        }

        c = buffer[buffer_index++];
        
        /* Check for end of line */
        if (c == '\n')
            break;

        /* Allocate memory for the line */
        line = realloc(line, line_index + 1);
        if (!line)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        line[line_index++] = c;
    }

    /* Null-terminate the line */
    if (line)
        line[line_index] = '\0';

    return line;
}
