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

    debuggePID = fork();
    if (debuggePID == -1) {
        fprintf(stderr, "Error forking: %s\n", strerror(errno));
        exit(-1);
    }

    if (debuggePID == 0) {
        // Exec child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    } else {
        // Exec Debugger Logic
        printf("Starting debugging process [pid %d]\n", debuggePID);
        mainDebuggerLoop();
    }

    return 0;
}
