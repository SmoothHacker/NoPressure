#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ptrace.h>

#include "debugger.h"

int main(int argc, char **argv, char **envp) {
    printf("NoPressure Linux Debugger\n");
    if (argc != 2 || strcmp(argv[1], "-h") == 0) {
        fprintf(stderr, "\tUsage: ./NoPressure BINARY");
        exit(-1);
    }

    printf("Loading %s for debugging\n", argv[1]);
    dbgSession dbgHandle;
    char *progName = strrchr(argv[1], '/');
    dbgHandle.programName = ++progName;
    dbgHandle.isRunning = false;
    dbgHandle.exePath = argv[1];

    printf("Loading %s for debugging\n", dbgHandle.programName);

    dbgHandle.PID = fork();
    if (dbgHandle.PID == -1) {
        fprintf(stderr, "Error forking: %s\n", strerror(errno));
        exit(-1);
    }

    if (dbgHandle.PID == 0) {
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
        printf("Starting debugging process [PID %d]\n", dbgHandle.PID);
        waitpid(dbgHandle.PID, &wait_status, __WALL);
        mainDebuggerLoop(&dbgHandle);
    }

    fclose(dbgHandle.elfFD);
    free(dbgHandle.elfHeader);
    return 0;
}
