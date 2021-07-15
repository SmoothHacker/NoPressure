#ifndef NOPRESSURE_DEBUGGER_H
#define NOPRESSURE_DEBUGGER_H

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>

__pid_t debuggePID;

void mainDebuggerLoop();
int handleCommandInput(char *line);
void printRegisters();
void continueExec();

#endif //NOPRESSURE_DEBUGGER_H
