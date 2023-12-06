#ifndef SHELL_H
#define SHELL_H

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"

void initializeShell();
char* readInput();
void executeCommand(char* command);
void printPrompt();

#endif /* SHELL_H */
