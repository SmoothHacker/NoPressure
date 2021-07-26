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
    dbgSession dbgHandle;
    char *progName = strrchr(argv[1], '/');
    dbgHandle.programName = ++progName;
    dbgHandle.isRunning = false;

    printf("Loading %s for debugging\n", dbgHandle.programName);

    dbgHandle.programPID = fork();
    if (dbgHandle.programPID == -1) {
        fprintf(stderr, "Error forking: %s\n", strerror(errno));
        exit(-1);
    }

    if (dbgHandle.programPID == 0) {
        // Exec child process
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
            fprintf(stderr, "Error in ptrace\n");
            exit(-1);
        }
        if(execl(argv[1], argv[1]) < 0) {
            perror("Execve Failed");
        }
    } else {
        // Exec Debugger Logic
        int wait_status;
        printf("Starting debugging process [pid %d]\n", dbgHandle.programPID);
        waitpid(dbgHandle.programPID, &wait_status, __WALL);
        mainDebuggerLoop(&dbgHandle);
    }

    return 0;
}
