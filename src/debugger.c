#include "debugger.h"

void mainDebuggerLoop() {
    int wait_status;
    int options = 0;
    waitpid(debuggePID, &wait_status, options);

    char line[250];
    printf("NoPressure> ");
    while(fgets(line, 250, stdin) != NULL) {
        int commandResult = handleCommandInput(line);
        switch (commandResult) {
            case 1:
                printRegisters();
                break;
            case 2:
                continueExec();
                break;
            case 3:
                exit(0);
            default:
                printf("Unknown Command\n");
                break;
        }

        printf("NoPressure> ");
    }
};

int handleCommandInput(char *line) {
    if(!strcmp("info registers\n", line)) {
        return 1;
    } else if (!strcmp("continue\n", line)) {
        return 2;
    } else if (!strcmp("q\n", line)) {
        return 3;
    }
};

void printRegisters() {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, debuggePID, NULL, &regs);
    printf("rax: %llu\n", regs.rax);
};

void continueExec() {
    ptrace(PTRACE_CONT, debuggePID, NULL, NULL);
    int wait_status;
    int options = 0;
    waitpid(debuggePID,&wait_status, options);
};
