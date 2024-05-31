#include "linked_list.h"

/*

linked_list.c
-------------
Contains linked list implementation for pman,
see linked_list.h for struct declaration & concise summary of functions.
- node/head: pointer to node/head
- pid: process id
- path: path to executable

*/

Node *head = NULL; // global head

// Checks if node in list by PID
Node *exists(Node *node, pid_t pid) {
    while (node) { // Search list for node:
        if (node->pid == pid) return node; // ret if found
        node = node->next;
    }
    return NULL; // node not found
}

 // Prints list of nodes
void printList(Node *node) {
    while (node) { // Iterate thru list:
        printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run); // print attributes
        node = node->next;
    }
}

// Adds node to list
void addNode(Node **head, pid_t pid, char *path) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) { // Error: malloc()
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node->pid = pid; // set node attributes
    if (!(node->path = strdup(path))) { // Error: strdup
        perror("Memory allocation failed");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->run = 1; // set node as running
    node->next = NULL; // set as last node in list
    while (*head) head = &(*head)->next; // find end of list
    *head = node; // insert node
}

// Removes node from list by PID
void deleteNode(Node **head, pid_t pid) { 
    if (!*head) { // List empty:
        printf("The process list is already empty.\n");
        return;
    }
    Node *temp = *head, *prev = NULL; // create prev
    while (temp && temp->pid != pid) { // Find node, tracking prev:
        prev = temp;
        temp = temp->next;
    }
    if (!temp) { // Error: Node not in list
        printf("Node with PID %d not found.\n", pid);
        return;
    }
    if (temp == *head) *head = temp->next; // remove node
    else prev->next = temp->next; // remove node
    free(temp->path), free(temp); // free dynamic attributes and node
}

// Update 'run' attributes & list
void update() {
    pid_t pid;
    int p_stat; // holds status of chuld process
    while (1) { // While still child processes to wait for:
        pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED); // get pid
        if (pid <= 0) break; // brek condition: no remaining children
        Node *node = exists(head, pid); // null if nonexistent
        if (node != NULL) { // If node exists:
            if (WIFCONTINUED(p_stat)) { // If started, set run=1
                printf("Process %d started.\n", pid);
                node->run = 1;
            } else if (WIFSTOPPED(p_stat)) { // If stopped, set run=0
                printf("Process %d stopped.\n", pid);
                node->run = 0;
            } else if (WIFSIGNALED(p_stat)) { // If killed, delete
                deleteNode(&head, pid);
                printf("Process %d killed.\n", pid);
            } else if (WIFEXITED(p_stat)) {
                deleteNode(&head, pid); // If terminated, delete
                printf("Process %d terminated.\n", pid);
            }
        }
    }
}

