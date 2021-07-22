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
#include <elf.h>
#include <capstone/capstone.h>

typedef struct {
    char *programName;
    bool isRunning;
    struct user_regs_struct* programRegs;
    __pid_t programPID;
    uint64_t baseAddress;
    FILE *elfFD;
} dbgSession;

enum Command{
    PRINT_REGISTERS,
    CONTINUE,
    QUIT,
    SINGLE_STEP
};

void mainDebuggerLoop(dbgSession *dbgHandle);
int handleCommandInput(char *line);
int printRegisters(dbgSession *dbgHandle);
int continueExec(dbgSession *dbgHandle);
int singleStep(dbgSession *dbgHandle);
int printDisassembly(dbgSession *dbgHandle);
int debugSetup(dbgSession *dbgHandle);

#endif //NOPRESSURE_DEBUGGER_H
