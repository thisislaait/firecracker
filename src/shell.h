#ifndef SHELL_H
#define SHELL_H

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"

void initializeShell(void);
char *readInput(void);
void executeCommand(char *command);
void printPrompt(void);

#endif /* SHELL_H */
