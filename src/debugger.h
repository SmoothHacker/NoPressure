#ifndef NOPRESSURE_DEBUGGER_H
#define NOPRESSURE_DEBUGGER_H

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <capstone/capstone.h>

typedef struct {
    char *programName;
    bool isRunning;
    struct user_regs_struct* programRegs;
    __pid_t programPID;
} debugSession;

enum Command{
    PRINT_REGISTERS,
    CONTINUE,
    QUIT,
    SINGLE_STEP
};

void mainDebuggerLoop(debugSession *debugHandle);
int handleCommandInput(char *line);
int printRegisters(debugSession *debugHandle);
int continueExec(debugSession *debugHandle);
int singleStep(debugSession *debugHandle);
int printDisassembly(debugSession *debugHandle);

#endif //NOPRESSURE_DEBUGGER_H
