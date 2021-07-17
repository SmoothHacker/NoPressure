#include "debugger.h"

char NoPressurex64_regs[27][10] = {
        "r15", "r14", "r13", "r12", "rbp",
        "rbx", "r11", "r10", "r9", "r8", "rax",
        "rcx", "rdx","rsi", "rdi", "orig_rax",
        "rip", "cs", "eflags", "rsp", "ss", "fs_base",
        "gs_base", "ds", "es", "fs", "gs"
};

void mainDebuggerLoop() {
    int wait_status;
    int options = 0;
    waitpid(debuggePID, &wait_status, options);

    char line[250];
    printf("NoPressure> ");
    while(fgets(line, 250, stdin) != NULL) {
        int commandResult = handleCommandInput(line);
        switch (commandResult) {
            case PRINT_REGISTERS: printRegisters(); break;
            case CONTINUE: continueExec(); break;
            case QUIT: exit(0); break;
            default: printf("Unknown Command\n"); break;
        }

        printf("NoPressure> ");
    }
};

int handleCommandInput(char *line) {
    if(!strcmp("info registers\n", line)) {
        return PRINT_REGISTERS;
    } else if (!strcmp("continue\n", line)) {
        return CONTINUE;
    } else if (!strcmp("q\n", line)) {
        return QUIT;
    }
};

void printRegisters() {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, debuggePID, NULL, &regs);
    unsigned long long *regPtr = &regs.rax;
    for (int i = 0; i < 27; ++i) {
        printf("%s: 0x%x\n", NoPressurex64_regs[i], *regPtr++);
    }
};

void continueExec() {
    ptrace(PTRACE_CONT, debuggePID, NULL, NULL);
    int wait_status;
    int options = 0;
    waitpid(debuggePID,&wait_status, options);
};
