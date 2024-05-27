#include "linked_list.h"
#include <stdio.h>

// Function to retrieve process data based on the PID using pstat
void populateNode(pid_t pid, Node *node) {
    // pid_t pid = atoi(pid); // Convert PID string to integer

    // Check if PID is valid
    if (pid <= 0) {
        printf("Error: Invalid PID.\n");
        return;
    }

    // Open the stat file of the process
    char stat_path[50];
    sprintf(stat_path, "/proc/%d/stat", pid);
    FILE *stat_file = fopen(stat_path, "r");
    if (stat_file == NULL) {
        printf("Error: Failed to open stat file for PID %d.\n", pid);
        return;
    }

    // Read stat data
    char comm[256], state;
    unsigned long utime, stime;
    long rss;
    unsigned long voluntary_ctxt_switches, nonvoluntary_ctxt_switches;

    // if (fscanf(stat_file, "%*d %s %c %*d %*d %*d %*d %*d %*lu %*lu %*lu %*lu %lu %lu %ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*llu %*lu %*ld %*lu %*lu %*lu %*lu %*lu %*ld %*lu %*lu %*llu %*lu %lu %lu", comm, &state, &utime, &stime, &rss, &voluntary_ctxt_switches, &nonvoluntary_ctxt_switches) != 7) {
    //     printf("Error: Failed to read stat data for PID %d.\n", pid);
    //     fclose(stat_file);
    //     return;
    // }


    // Close the stat file
    fclose(stat_file);

    // Populate the node with retrieved information
    strcpy(node->filename, comm);
    node->state = state;
    node->utime = utime;
    node->stime = stime;
    node->rss = rss;
    node->voluntary_ctxt_switches = voluntary_ctxt_switches;
    node->nonvoluntary_ctxt_switches = nonvoluntary_ctxt_switches;
}

// Function to add a new node with relevant information based on the PID
Node *add_newNode(Node *head, pid_t new_pid) {
    Node *new_node = (Node *)malloc(sizeof(Node)); // Allocate memory for the new node
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Populate the new node with relevant information
    populateNode(new_pid, new_node);
    new_node->pid = new_pid;
    new_node->next = head; // Set the next pointer of the new node to the current head
    return new_node; // Return the new node as the new head of the list
}

// Node *add_newNode(Node *head, pid_t new_pid, char *new_filename, char state, double utime, double stime, int rss, int voluntary_ctxt_switches, int nonvoluntary_ctxt_switches) {
//     Node *new_node = (Node *)malloc(sizeof(Node)); // Allocate memory for the new node
//     if (new_node == NULL) {
//         fprintf(stderr, "Error: Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     new_node->pid = new_pid;
//     new_node->filename = new_filename;
//     new_node->state = state;
//     new_node->utime = utime;
//     new_node->stime = stime;
//     new_node->rss = rss;
//     new_node->voluntary_ctxt_switches = voluntary_ctxt_switches;
//     new_node->nonvoluntary_ctxt_switches = nonvoluntary_ctxt_switches;
//     new_node->next = head; // Set the next pointer of the new node to the current head
//     return new_node; // Return the new node as the new head of the list
// }

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