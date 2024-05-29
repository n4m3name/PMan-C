#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "linked_list.h"

#define MAX_ARGS 128 // Define the maximum number of arguments

// --------------------------------

// Define the node structure
typedef struct Node {
    pid_t pid;
    char *path;
    int run;
    struct Node *next;
} Node;

Node *head = NULL;

Node *exists(Node *node, pid_t pid) {
    if (node == NULL) {
        return NULL;  // Return NULL if the list is empty
    }

    while (node != NULL) {
        if (node->pid == pid) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void printList(Node *node) {
    printf("PrintList:\n");
    if (node == NULL) {
        return; // Return if the list is empty
    }

    Node *current = node; // Create a local copy of the pointer
    while (current != NULL) {
        printf("PID: %d, Path: %s, Running: %d\n", current->pid, current->path, current->run);
        current = current->next;
    }
}

void addNode(Node **head, pid_t pid, char *path) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node->pid = pid;
    node->path = strdup(path); // Duplicate the path string
    if (node->path == NULL) {
        perror("Memory allocation failed");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->run = 1;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }

    printf("%d, %s, %d\n", node->pid, node->path, node->run);
    printList(*head);
}

void printNode(Node *node) {
    if (node == NULL) {
        printf("Null\n");
    } else {
        printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
    }
}

void deleteNode(Node **head, pid_t pid) {
    if (*head == NULL) {
        printf("The process list is already empty.\n");
        return;
    }

    Node *temp = *head;
    Node *prev = NULL;

    // Traverse the list to find the node to be deleted
    while (temp != NULL && temp->pid != pid) {
        prev = temp;
        temp = temp->next;
    }

    // If the node was not found
    if (temp == NULL) {
        printf("Node with PID %d not found.\n", pid);
        return;
    }

    // If the node to be deleted is the head
    if (temp == *head) {
        *head = temp->next; // Update head to point to the next node
    } else {
        prev->next = temp->next;
    }

    // Free memory allocated for path and the node itself
    free(temp->path);
    free(temp);

    printf("Node with PID %d deleted.\n", pid);
    printNode(*head);
}

// --------------------------------

void bg(char **input) {
    if (input[1] == NULL) {
        printf("Usage: bg <command>\n");
        return;
    }
    pid_t pid = fork(); 
    if (pid == 0) { // Child process
        execvp(input[1], &input[1]); // Execute the specified program with arguments
        printf("Execution failed\n");
        exit(1);
    } else if (pid > 0) {
        printf("Started process %d\n", pid);
        addNode(&head, pid, input[1]); // Assuming input[1] contains the path to the executable
        sleep(1);
    } else {
        printf("Failed to fork");
    }
}

void bgkill(char *str_pid) {
    if (str_pid == NULL) {
        fprintf(stderr, "Usage: bgkill <pid>\n");
        return;
    }
    pid_t pid = atoi(str_pid); // Convert the second argument to PID
    if (pid == 0) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if(kill(pid, SIGTERM)){
        printf("Error: failed to execute bgkill\n");
    };

    deleteNode(&head, pid); // Remove the node with the given PID
    printf("Process with PID %d killed and removed from the list.\n", pid);
}

void bglist() {
    printf("BGList:\n");
    if (head == NULL) {
        printf("The process list is empty.\n");
        return;
    }
    printNode(head);
    printList(head); // Pass a copy of the head pointer
}

void bgstop(char *str_pid) {
    // Your code here
    printf("BGStop\n");
}

void bgstart(char *str_pid) {
    // Your code here
    printf("BGStart\n");
}

void pstat(char *str_pid) {
    // Your code here
    printf("Pstat\n");
}


void updateRun() {
    printf("UpdateRun:\n");
    pid_t pid;
    int p_stat;
    while (1) {
        pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED);
        if (pid <= 0) {
            break;
        }

        Node *node = exists(head, pid);
        if (node == NULL) {
            // Process not found in the list, skip it
            continue;
        } else if (WIFSTOPPED(p_stat)) {
            printf("Process %d stopped.\n", pid);
            node->run = 0;
        } else if (WIFCONTINUED(p_stat)) {
            printf("Process %d started.\n", pid);
            node->run = 1;
        } else if (WIFSIGNALED(p_stat)) {
            deleteNode(&head, pid);
            // head = NULL;
            printf("Process %d killed.\n", pid);
        } else if (WIFEXITED(p_stat)) {
            deleteNode(&head, pid);
            // head = NULL;
            printf("Process %d terminated.\n", pid);
        }
    }
}

void genHelp() {
    printf("Available commands:\n");
    printf("  bg       - Start a program in the background\n");
    printf("  bgkill   - Kill a background program\n");
    printf("  bglist   - List all running background programs\n");
    printf("  bgstart  - Start a stopped background program\n");
    printf("  bgstop   - Stop a running background program\n");
    printf("  pstat    - Display statistics of a background program\n");
    printf("  q        - Quit the program\n");
}

void redir(char **input) {
    if (input[0] == NULL) {
        printf("Invalid input, try 'h' for available commands.\n");
        return;
    }
    if (strcmp(input[0], "bg") == 0) bg(input);
    else if (strcmp(input[0], "bgkill") == 0) bgkill(input[1]);
    else if (strcmp(input[0], "bglist") == 0) bglist();
    else if (strcmp(input[0], "bgstart") == 0) bgstart(input[1]);
    else if (strcmp(input[0], "bgstop") == 0) bgstop(input[1]);
    else if (strcmp(input[0], "pstat") == 0) pstat(input[1]);
    else if (strcmp(input[0], "h") == 0) genHelp();
    else if (strcmp(input[0], "q") == 0) exit(0); // Exit the program
    else printf("Invalid input, try 'h' for available commands.\n");
}

void getInput(char **input) {
    char *line = readline("pman>");
    if (line && strcmp(line, "")!=0) { // Check if it's not null or empty
        add_history(line); // Add input to history
        char *token = strtok(line, " "); // Tokenize input
        int i = 0;
        while (token && i < MAX_ARGS) {
            input[i++] = strdup(token); // Store the token in the args array
            token = strtok(NULL, " "); // Get the next token
        }
        input[i] = NULL; // Null terminate array
        if (i == MAX_ARGS && token != NULL) {
            fprintf(stderr, "Error: Too many arguments\n");
            for (int j = 0; input[j] != NULL; j++) {
                free(input[j]); // Free allocated memory
            }
        }
        free(line);
    }
}


int main(int argc, char *argv[]) {
    // Error handling: CL args
    if (argc > 1) { // if args...
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1; // error
    }
    while(1){ // Inf loop
        char *input[MAX_ARGS+1]; // Holds user input
        for (int i = 0; i < MAX_ARGS; i++) input[i] = NULL;
        getInput(input); // Get user input
        redir(input); // redirect ro relevant function
        for (int i = 0; input[i] != NULL; i++) free(input[i]); // free allocated memory 
        updateRun(); // check & update running processes
    }

}


