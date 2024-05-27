#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

// Struct to represent a node in the linked list
typedef struct Node {
    pid_t pid;           // Process ID
    char *filename;      // Filename of the executable
    char state;          // Process state
    double utime;        // Amount of time in user mode
    double stime;        // Amount of time in kernel mode
    int rss;             // Resident Set Size
    int voluntary_ctxt_switches;    // Voluntary context switches
    int nonvoluntary_ctxt_switches; // Non-voluntary context switches
    struct Node *next;   // Pointer to the next node in the list
} Node;

// Function prototypes
Node *add_newNode(Node *head, pid_t new_pid, char *new_filename, char state, double utime, double stime, int rss, int voluntary_ctxt_switches, int nonvoluntary_ctxt_switches);
Node *deleteNode(Node *head, pid_t pid);
void printList(Node *node);
int PifExist(Node *node, pid_t pid);

#endif
