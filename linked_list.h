#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Req'd libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Struct declaration
typedef struct Node {
    pid_t pid; // process id
    char *path; // path to executable
    int run; // 1: running, 0: stopped
    struct Node *next;
} Node;

// Function declaration
Node *exists(Node *node, pid_t pid); // check if node in list
void printList(Node *node); // print list of nodes
void addNode(Node **head, pid_t pid, char *path); // add node to end of list
void deleteNode(Node **head, pid_t pid); // delete node from list
void update(); // // update 'run' attributes & list

#endif /* LINKED_LIST_H */