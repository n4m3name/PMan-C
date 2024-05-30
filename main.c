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
    // printf("PrintList:\n");
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

void updateRun() {
    // printf("UpdateRun:\n");
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
    // updateRun();
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
    if(kill(pid, SIGTERM)) {
        printf("Execution failed\n");
    } else {
        sleep(1);
    }

    deleteNode(&head, pid); // Remove the node with the given PID
    printf("Process with PID %d killed and removed from the list.\n", pid);
    // updateRun();
}

void bglist() {
    // printf("BGList:\n");
    // updateRun(); // check & update running processes
    if (head == NULL) {
        printf("The process list is empty.\n");
        return;
    }
    // printNode(head);
    printList(head); // Pass a copy of the head pointer
    // updateRun();
}

void bgstop(char *str_pid) {
    if (str_pid == NULL) {
        fprintf(stderr, "Usage: bgstop <pid>\n");
        return;
    }
    pid_t pid = atoi(str_pid); // Convert the second argument to PID
    if (pid == 0) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if(kill(pid, SIGSTOP)) {
        printf("Execution failed\n");
    } else {
        sleep(1);
    }
    // updateRun();

    // deleteNode(&head, pid); // Remove the node with the given PID
    // printf("Process with PID %d killed and removed from the list.\n", pid);
}

void bgstart(char *str_pid) {
    if (str_pid == NULL) {
        fprintf(stderr, "Usage: bgstart <pid>\n");
        return;
    }
    pid_t pid = atoi(str_pid); // Convert the second argument to PID
    if (pid == 0) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if(kill(pid, SIGCONT)) {
        printf("Execution failed\n");
    } else {
        sleep(1);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void pstat(char *sPid) {

    if (sPid == NULL) {
        fprintf(stderr, "Usage: bgstop <pid>\n");
        return;
    }
    pid_t pid = atoi(sPid); // Convert the second argument to PID
    if (pid == 0) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    // Open the stat file of the process
    char stat_path[50];
    sprintf(stat_path, "/proc/%d/stat", pid);
    FILE *stat_file = fopen(stat_path, "r");
    if (stat_file == NULL) {
        printf("Error: Process %d does not exist.\n", pid);
        return;
    }

    // Read stat data
    char comm[256], state;
    unsigned long utimeRaw, stimeRaw;
    long rss;

    if (fscanf(stat_file, "%*d (%[^)]) %c %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %*s %*s %ld %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s",
               comm, &state, &utimeRaw, &stimeRaw, &rss) != 5) {
        printf("Error: Failed to read stat data for PID %d.\n", pid);
        fclose(stat_file);
        return;
    }

    // Close the stat file
    fclose(stat_file);

    float utime = utimeRaw/100.0;
    float stime = stimeRaw/100.0;

    // Read status file for context switches
    char status_path[50];
    sprintf(status_path, "/proc/%d/status", pid);
    FILE *status_file = fopen(status_path, "r");
    if (status_file == NULL) {
        printf("Error: Failed to open status file for PID %d.\n", pid);
        return;
    }

    char line[256];
    unsigned long voluntary_ctxt_switches = 0, nonvoluntary_ctxt_switches = 0;
    while (fgets(line, sizeof(line), status_file)) {
        if (sscanf(line, "voluntary_ctxt_switches: %lu", &voluntary_ctxt_switches) == 1 ||
            sscanf(line, "nonvoluntary_ctxt_switches: %lu", &nonvoluntary_ctxt_switches) == 1) {
            // Read values if they match the patterns
        }
    }

    fclose(status_file);

    // Print the retrieved information
    printf("comm:\t%s\n", comm);
    printf("state:\t%c\n", state);
    printf("utime:\t%.2f seconds\n", utime);
    printf("stime:\t%.2f seconds\n", stime);
    printf("rss:\t%ld\n", rss);
    printf("voluntary ctxt switches:\t%lu\n", voluntary_ctxt_switches);
    printf("nonvoluntary ctxt switches:\t%lu\n", nonvoluntary_ctxt_switches);
}



// void pstat(char *str_pid) {
//     // Your code here
//     printf("Pstat\n");
// }


// void updateRun() {
//     // printf("UpdateRun:\n");
//     pid_t pid;
//     int p_stat;
//     while (1) {
//         pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED);
//         if (pid <= 0) {
//             break;
//         }

//         Node *node = exists(head, pid);
//         if (node == NULL) {
//             // Process not found in the list, skip it
//             continue;
//         } else if (WIFSTOPPED(p_stat)) {
//             printf("Process %d stopped.\n", pid);
//             node->run = 0;
//         } else if (WIFCONTINUED(p_stat)) {
//             printf("Process %d started.\n", pid);
//             node->run = 1;
//         } else if (WIFSIGNALED(p_stat)) {
//             deleteNode(&head, pid);
//             // head = NULL;
//             printf("Process %d killed.\n", pid);
//         } else if (WIFEXITED(p_stat)) {
//             deleteNode(&head, pid);
//             // head = NULL;
//             printf("Process %d terminated.\n", pid);
//         }
//     }
// }

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
    char *line = readline("pman> ");
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
        // updateRun(); // check & update running processes
        char *input[MAX_ARGS+1]; // Holds user input
        for (int i = 0; i < MAX_ARGS; i++) input[i] = NULL;
        getInput(input); // Get user input
        redir(input); // redirect ro relevant function
        for (int i = 0; input[i] != NULL; i++) free(input[i]); // free allocated memory 
        updateRun(); // check & update running processes
    }

}


