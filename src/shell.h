#ifndef SHELL_H
#define SHELL_H

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"

#include <sys/types.h>

extern char **environ;

void initializeShell(void);
char *readInput(void);
void executeCommand(char *command);
void printPrompt(void);
void splitCommand(char *command, char *argv[], int maxArgs);
void executeChild(char *argv[]);
void executeParent(pid_t pid);
void searchAndExecute(char *command, char *argv[]);
void env_builtin(void);

#endif /* SHELL_H */
