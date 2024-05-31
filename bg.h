#ifndef BG_H
#define BG_H

// Req'd libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "linked_list.h"

extern Node *head; // declared in linked_list

// Function declaration
void bg(char **input);  // start background process
int checkProcessExists(Node *head, pid_t pid); // Check if process exists in the list
void bgkill(char *str_pid); // kill background process by PID
void bglist(); // list running processes
void bgstop(char *str_pid); // stop background process by PID
void bgstart(char *str_pid); // resume background process by PID

#endif /* BG_H */
