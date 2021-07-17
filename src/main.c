#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ptrace.h>

#include "debugger.h"

__pid_t debuggePID;

int main(int argc, char **argv) {
    printf("NoPressure (2021) Debugger\n");
    if (argc != 2 || strcmp(argv[1], "-h") == 0) {
        printf("\tUsage: NoPressure BINARY");
        return 1;
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
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(debugHandle.programName, debugHandle.programName, NULL);
    } else {
        // Exec Debugger Logic
        printf("Starting debugging process [pid %d]\n", debugHandle.programPID);
        mainDebuggerLoop(&debugHandle);
    }

    return 0;
}
