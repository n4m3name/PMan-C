#include "linked_list.h"
#include <stdio.h>

Node *add_newNode(Node *head, pid_t new_pid, char *new_filename, char state, double utime, double stime, int rss, int voluntary_ctxt_switches, int nonvoluntary_ctxt_switches) {
    Node *new_node = (Node *)malloc(sizeof(Node)); // Allocate memory for the new node
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->pid = new_pid;
    new_node->filename = new_filename;
    new_node->state = state;
    new_node->utime = utime;
    new_node->stime = stime;
    new_node->rss = rss;
    new_node->voluntary_ctxt_switches = voluntary_ctxt_switches;
    new_node->nonvoluntary_ctxt_switches = nonvoluntary_ctxt_switches;
    new_node->next = head; // Set the next pointer of the new node to the current head
    return new_node; // Return the new node as the new head of the list
}

Node *deleteNode(Node *head, pid_t pid) {
    Node *current = head;
    Node *prev = NULL;

    // Traverse the list to find the node with the given pid
    while (current != NULL && current->pid != pid) {
        prev = current;
        current = current->next;
    }

    // If the node with the given pid is found
    if (current != NULL) {
        // If the node to be deleted is the head of the list
        if (prev == NULL) {
            head = head->next;
        } else {
            prev->next = current->next;
        }
        free(current); // Free the memory allocated for the node
    } else {
        fprintf(stderr, "Error: Process %d does not exist.\n", pid);
    }

    return head; // Return the updated head of the list
}

void printList(Node *node) {
    while (node != NULL) {
        printf("PID: %d, Filename: %s, State: %c, utime: %lf, stime: %lf, rss: %d, voluntary_ctxt_switches: %d, nonvoluntary_ctxt_switches: %d\n",
               node->pid, node->filename, node->state, node->utime, node->stime, node->rss,
               node->voluntary_ctxt_switches, node->nonvoluntary_ctxt_switches);
        node = node->next; // Move to the next node
    }
}

int PifExist(Node *node, pid_t pid) {
    while (node != NULL) {
        if (node->pid == pid) {
            return 1; // Process with the given pid exists
        }
        node = node->next; // Move to the next node
    }
    return 0; // Process with the given pid does not exist
}


