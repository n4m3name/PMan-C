#ifndef PSTAT_H
#define PSTAT_H

// Req'd libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bg.h"

extern Node *head; // declared in linked_list

// Function declaration
int validateInputPid(char *sPid); // validate input PID, convert to int
int readStatFile(pid_t pid, char *comm, char *state, unsigned long *utimeRaw, unsigned long *stimeRaw, long *rss); // read process information from /proc/[PID]/stat file
int readStatusFile(pid_t pid, unsigned long *voluntary_ctxt_switches, unsigned long *nonvoluntary_ctxt_switches); // read context switch information from /proc/[PID]/status file
void pstat(char *sPid); // run pstat & output results

#endif /* PSTAT_H */
