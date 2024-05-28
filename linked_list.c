#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "linked_list.h"

Node *addNode(Node *head, pid_t pid, char *path){
    Node *node = (Node *)malloc(sizeof(Node));
    // Handle mem allocation failure
	if (node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
	// Set val's
    node->pid = pid; // process id
    node->path = strdup(path); // path to exec
    node->next = NULL; // next
	node->run = 1; // currently running, default yes
	// If 1st, ret
    if (head == NULL) {
        return node;
    }
	// Else add to end of list
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    return head;
}

Node *deleteNode(Node *head, pid_t pid){
	// If none, ret
    if (head == NULL) {
        return NULL;
    }
	// If 1st, del
    if (head->pid == pid) {
        Node *temp = head->next;
        free(head->path);
        free(head);
        return temp;
    }
	// Else find & del
    Node *prev = head;
    Node *curr = head->next;
    while (curr != NULL) {
        if (curr->pid == pid) {
            prev->next = curr->next;
            free(curr->path);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

void printList(Node *node){
	// Iterate & print
    while (node != NULL) {
        printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
        node = node->next;
    }
}

Node *exists(Node *node, pid_t pid){
    while (node != NULL) {
        if (node->pid == pid) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}


void updateRun(Node *head){
    pid_t pid;
    int p_stat;
    while (1) {
        pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED); // wait for relevant child process
		if (pid<=0) break; // if none, break
		Node *node = exists(head, pid); // check if process in list
        if (WIFSTOPPED(p_stat)){ // handle WIFSTOPPED
            printf("Process %d stopped.\n", pid);
            if (node) node->run = 0; // set run = F (0)
        }
        if (WIFCONTINUED(p_stat)) { // handle WIFCONTINUED
            printf("Process %d started.\n", pid);
            if (node) node->run = 1; // set run = T (1)
        }
        if (WIFSIGNALED(p_stat)) { // handle WIFSIGNALED
            printf("Process %d killed.\n", pid);
            deleteNode(head, pid); // delete from list
        }
        if (WIFEXITED(p_stat)) { // handle WIFEXITED
            printf("Process %d terminated.\n", pid);
            deleteNode(head, pid); // delete from list
        }
    }
}

