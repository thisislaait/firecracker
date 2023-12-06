#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
void executeCommand(char* command) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;
    LPVOID errorMsg;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    /* Split the command into executable and arguments */
    char* executable = strtok(command, " ");
    char* arguments[10];

    int i = 0;
    while (i < 9 && (arguments[i] = strtok(NULL, " ")) != NULL) {
        i++;
    }
    arguments[i] = NULL; /* Null-terminate the argument list */

    if (!CreateProcess(NULL, executable, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "Error creating process: %lu\n", GetLastError());
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            0,
            (LPSTR)&errorMsg,
            0,
            NULL
        );

        fprintf(stderr, "Error message: %s\n", (LPSTR)errorMsg);
        LocalFree(errorMsg);
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        fprintf(stderr, "Error getting exit code: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        fprintf(stderr, "Command exited with code %lu\n", exitCode);
    }

}
#endif  // _WIN32
