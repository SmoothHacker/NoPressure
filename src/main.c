#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ptrace.h>

#include "debugger.h"

int main(int argc, char **argv, char **envp) {
    printf("NoPressure Linux Debugger\n");
    if (argc != 2 || strcmp(argv[1], "-h") == 0) {
        fprintf(stderr, "\tUsage: NoPressure BINARY");
        exit(-1);
    }

    printf("Loading %s for debugging\n", argv[1]);
    debugSession debugHandle;
    debugHandle.programName = argv[1];
    debugHandle.isRunning = false;

    debugHandle.programPID = fork();
    if (debugHandle.programPID == -1) {
        fprintf(stderr, "Error forking: %s\n", strerror(errno));
        exit(-1);
    }

    if (debugHandle.programPID == 0) {
        // Exec child process
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL)) {
            fprintf(stderr, "Error forking: %s\n", strerror(errno));
            exit(-1);
        }
        execl(debugHandle.programName, debugHandle.programName, envp);
    } else {
        // Exec Debugger Logic
        printf("Starting debugging process [pid %d]\n", debugHandle.programPID);
        mainDebuggerLoop(&debugHandle);
        fprintf(stderr, "Detaching\n");
        ptrace(PTRACE_DETACH, debugHandle.programPID, 0, 0);
    }

    return 0;
}
