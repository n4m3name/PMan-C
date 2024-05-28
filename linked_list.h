#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

// Define the node structure
typedef struct Node {
    pid_t pid;
    char *path;
    int run;
    struct Node *next;
} Node;

// Function prototypes
Node *addNode(Node *head, pid_t pid, char *path);
Node *deleteNode(Node *head, pid_t pid);
void printList(Node *node);
Node *exists(Node *node, pid_t pid);
void updateRun(Node *head);

#endif /* PROCESS_LIST_H */