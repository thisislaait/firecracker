#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <windows.h> Include only for Windows */
#include "shell.h"

void executeCommand(char* command) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;
    LPVOID errorMsg;

    char* executable;
    char* arguments[10];
    int i;  /*Declare i at the beginning*/

    executable = strtok(command, " ");

    if (!executable) {
        fprintf(stderr, ANSI_COLOR_RED "Error: No command specified\n" ANSI_COLOR_RESET);
        return;
    }

    for (i = 0; i < 10; i++) {
        arguments[i] = NULL;
    }

    for (i = 0; i < 9; i++) {
        arguments[i] = strtok(NULL, " ");
        if (!arguments[i]) {
            break;
        }
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, executable, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, ANSI_COLOR_RED "Error creating process: %lu\n" ANSI_COLOR_RESET, GetLastError());
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            0,
            (LPSTR)&errorMsg,
            0,
            NULL
        );

        fprintf(stderr, ANSI_COLOR_RED "Error message: %s\n" ANSI_COLOR_RESET, (LPSTR)errorMsg);
        LocalFree(errorMsg);
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        fprintf(stderr, ANSI_COLOR_RED "Error getting exit code: %lu\n" ANSI_COLOR_RESET, GetLastError());
        exit(EXIT_FAILURE);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        fprintf(stderr, ANSI_COLOR_RED "Command exited with code %lu\n" ANSI_COLOR_RESET, exitCode);
    }
}

