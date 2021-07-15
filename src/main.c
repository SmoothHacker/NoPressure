#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>

#include "debugger.h"

int main(int argc, char **argv) {
    printf("NoPressure (2021) Debugger\n");
    if (argc != 2 || strcmp(argv[1], "-h") == 0) {
        printf("\tUsage: NoPressure BINARY");
        return 1;
    }

    printf("Loading %s for debugging\n", argv[1]);

    __pid_t pid = fork();
    if(pid == 0) {
        // Exec child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    } else {
        // Exec Debugger Logic
        debuggePID = pid;
        printf("Starting debugging process [pid %d]\n", pid);
        mainDebuggerLoop();
    }

    return 0;
}
