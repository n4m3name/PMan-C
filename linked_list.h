#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// Define the structure for a node in the linked list
typedef struct Node {
    pid_t pid; // Process ID
    char filename[256]; // Filename of the executable
    char state; // Process state
    double utime; // User mode CPU time
    double stime; // Kernel mode CPU time
    int rss; // Resident Set Size
    int voluntary_ctxt_switches; // Number of voluntary context switches
    int nonvoluntary_ctxt_switches; // Number of non-voluntary context switches
    struct Node *next; // Pointer to the next node
} Node;

// Function to retrieve process data based on the PID using pstat and populate the node
void populateNode(pid_t pid, Node *node);

// Function to add a new node with relevant information based on the PID
Node *add_newNode(Node *head, pid_t new_pid);

// Function to delete a node with the given PID from the linked list
Node *deleteNode(Node *head, pid_t pid);

// Function to print the linked list
void printList(Node *node);

// Function to check if a process with the given PID exists in the linked list
int PifExist(Node *node, pid_t pid);

// Function to start a program in the background
void bg(char *program_name);

#endif /* LINKED_LIST_H */

