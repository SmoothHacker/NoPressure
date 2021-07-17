#ifndef NOPRESSURE_DEBUGGER_H
#define NOPRESSURE_DEBUGGER_H

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>


extern __pid_t debuggePID;

enum Command{
    PRINT_REGISTERS,
    CONTINUE,
    QUIT,
    SINGLE_STEP
};

void mainDebuggerLoop();
int handleCommandInput(char *line);
int printRegisters();
int continueExec();
int singleStep();
int printDisassembly();

#endif //NOPRESSURE_DEBUGGER_H
