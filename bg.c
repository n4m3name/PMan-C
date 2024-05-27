// #include <stdio.h>
// #include "bg.h"

// void bg(char *arg) {
//     printf("BG\n");
//     printf("%s\n", arg);
// }

// void bgkill(char *arg) {
//     printf("BGKILL\n");
//     printf("%s\n", arg);
// }

// void bglist() {
//     printf("BGLIST\n");
// }

// void bgstart(char *arg) {
//     printf("BGSTART\n");
//     printf("%s\n", arg);
// }

// void bgstop(char *arg) {
//     printf("BGSTOP\n");
//     printf("%s\n", arg);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "linked_list.h" // Assuming you have defined Node and other related functions in linked_list.h

Node *head = NULL;

/*
BG
TODO:
- [ ] Create a node (pass head, pid) each time new process is create
*/

// Function to start a program in the background
void bg(char *program_name) {
    printf("%d\n", 69);
    pid_t pid = fork(); // Fork a new process
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        if (execlp(program_name, program_name, NULL) == -1) { // Execute the specified program
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        // Add the new process to the linked list
        head = add_newNode(head, pid);
    }
}

// Function to display a list of all background processes
void bglist() {
    Node *current = head; // Assuming 'head' is the head of your linked list containing background processes
    printf("List of background processes:\n");
    int count = 0;
    while (current != NULL) {
        printf("%d: %s\n", current->pid, current->filename);
        count++;
        current = current->next;
    }
    printf("Total background jobs: %d\n", count);
}

void bgkill(char *pid_str) {
    pid_t pid = atoi(pid_str); // Convert PID string to integer

    // Check if PID is valid
    if (pid <= 0) {
        printf("Error: Invalid PID.\n");
        return;
    }

    // Send TERM signal to the process
    if (kill(pid, SIGTERM) == -1) {
        perror("Failed to kill process");
        return;
    }

    // Wait for the child process to terminate
    waitpid(pid, NULL, 0);

    // Remove the process from the linked list
    head = deleteNode(head, pid);
}

// Function to send the STOP signal to temporarily stop a background job with the specified PID
void bgstop(pid_t pid) {
    if (kill(pid, SIGSTOP) == -1) { // Send STOP signal to the job with the specified PID
        perror("Failed to stop process");
    } else {
        printf("Background job with PID %d stopped.\n", pid);
    }
}

// Function to send the CONT signal to restart a background job with the specified PID
void bgstart(pid_t pid) {
    if (kill(pid, SIGCONT) == -1) { // Send CONT signal to the job with the specified PID
        perror("Failed to start process");
    } else {
        printf("Background job with PID %d started.\n", pid);
    }
}




