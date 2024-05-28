// #include <string.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <errno.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include "linked_list.h"

// #define MAX_ARGS 128 // Define the maximum number of arguments

// Node *head = NULL;

// void bg(char **input) {
//     pid_t pid = fork(); 
//     if (pid < 0) { // Failed
//         perror("Fork failed");
//         return;
//     } else if (pid == 0) { // Child process
//         if (execvp(input[1], &input[1]) == -1) { // Execute the specified program with arguments
//             perror("Execution failed");
//             exit(EXIT_FAILURE);
//         }
//     } else {
//         if (input[1] != NULL) { // Check if the command has an argument
//             head = addNode(head, pid, input[1]); // Assuming input[1] contains the path to the executable
//         }
//         printf("Added process with PID %d to the list.\n", pid);
//     }
// }

// // void bgkill(char *str_pid) {
// //     if (str_pid == NULL) {
// //         fprintf(stderr, "Usage: bgkill <pid>\n");
// //         return;
// //     }
// //     pid_t pid = atoi(str_pid); // Convert the second argument to PID
// //     if (pid == 0) {
// //         fprintf(stderr, "Invalid PID\n");
// //         return;
// //     }
// //     head = deleteNode(head, pid); // Remove the node with the given PID
// //     printf("Process with PID %d killed and removed from the list.\n", pid);
// // }

// // void bgkill(pid_t pid) {
// // 	if (!isExistingProcess(pid)) {
// // 		printf("Error: invalid pid\n");
// // 		return;
// // 	}
// // 	int error = kill(pid, SIGTERM);
// // 	if (!error) {
// // 		sleep(1);
// // 	} else {
// // 		printf("Error: failed to execute bgkill\n");
// // 	}
// // }

// void bgkill(char *str_pid) {
//     if (str_pid == NULL) {
//         fprintf(stderr, "Usage: bgkill <pid>\n");
//         return;
//     }
//     pid_t pid = atoi(str_pid); // Convert the second argument to PID
//     if (pid == 0) {
//         fprintf(stderr, "Invalid PID\n");
//         return;
//     }
//     head = deleteNode(head, pid); // Remove the node with the given PID
//     printf("Process with PID %d killed and removed from the list.\n", pid);
// }

// void bglist() {
//     if (head == NULL) {
//         printf("The process list is empty.\n");
//         return;
//     }
//     printf("Process list:\n");
//     printList(head); // Print the linked list
// }

// void bgstop(char *str_pid) {
//     // Your code here
//     printf("BGStop\n");
// }

// void bgstart(char *str_pid) {
//     // Your code here
//     printf("BGStart\n");
// }

// void pstat(char *str_pid) {
//     // Your code here
//     printf("Pstat\n");
// }

// void genHelp() {
//     printf("Available commands:\n");
//     printf("  bg       - Start a program in the background\n");
//     printf("  bgkill   - Kill a background program\n");
//     printf("  bglist   - List all running background programs\n");
//     printf("  bgstart  - Start a stopped background program\n");
//     printf("  bgstop   - Stop a running background program\n");
//     printf("  pstat    - Display statistics of a background program\n");
//     printf("  q        - Quit the program\n");
// }

// // void redir(char **input) {
// //     if (strcmp(input[0], "bg") == 0) bg(input);
// //     else if (strcmp(input[0], "bgkill") == 0) bgkill(input[1]);
// //     else if (strcmp(input[0], "bglist") == 0) bglist();
// //     else if (strcmp(input[0], "bgstart") == 0) bgstart(input[1]);
// //     else if (strcmp(input[0], "bgstop") == 0) bgstop(input[1]);
// //     else if (strcmp(input[0], "pstat") == 0) pstat(input[1]);
// //     else if (strcmp(input[0], "h") == 0) genHelp();
// //     else if (strcmp(input[0], "q") == 0) exit(0); // Exit the program
// //     else printf("Invalid input, try 'h' for available commands.\n");
// // }

// void redir(char **input) {
//     if (input[0] == NULL) {
//         printf("Invalid input, try 'h' for available commands.\n");
//         return;
//     }
//     if (strcmp(input[0], "bg") == 0) bg(input);
//     else if (strcmp(input[0], "bgkill") == 0) bgkill(input[1]);
//     else if (strcmp(input[0], "bglist") == 0) bglist();
//     else if (strcmp(input[0], "bgstart") == 0) bgstart(input[1]);
//     else if (strcmp(input[0], "bgstop") == 0) bgstop(input[1]);
//     else if (strcmp(input[0], "pstat") == 0) pstat(input[1]);
//     else if (strcmp(input[0], "h") == 0) genHelp();
//     else if (strcmp(input[0], "q") == 0) exit(0); // Exit the program
//     else printf("Invalid input, try 'h' for available commands.\n");
// }


// // void getInput(char **input) {
// //     char *line = readline("pman>");
// //     if (line && *line) { // Check if it's not null or empty
// //         add_history(line); // Add input to history
// //         char *token = strtok(line, " "); // Tokenize input
// //         int i = 0;
// //         while (token && i < MAX_ARGS) {
// //             input[i++] = strdup(token); // Store the token in the args array
// //             token = strtok(NULL, " "); // Get the next token
// //         }
// //         input[i] = NULL; // Null terminate array
// //         if (!input[0]) printf("Invalid input, try 'h' for available commands.\n");
// //     }
// //     free(line);
// // }

// void getInput(char **input) {
//     char *line = readline("pman>");
//     if (line && *line) { // Check if it's not null or empty
//         add_history(line); // Add input to history
//         char *token = strtok(line, " "); // Tokenize input
//         int i = 0;
//         while (token && i < MAX_ARGS) {
//             input[i++] = strdup(token); // Store the token in the args array
//             token = strtok(NULL, " "); // Get the next token
//         }
//         input[i] = NULL; // Null terminate array
//         if (i == MAX_ARGS && token != NULL) {
//             fprintf(stderr, "Error: Too many arguments\n");
//             for (int j = 0; input[j] != NULL; j++) {
//                 free(input[j]); // Free allocated memory
//             }
//         }
//     }
//     free(line);
// }


// int main(int argc, char *argv[]) {
//     // Error handling: CL args
//     if (argc > 1) { // if args...
//         fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
//         return 1; // error
//     }
//     while(1){ // Inf loop
//         char *input[MAX_ARGS+1]; // Holds user input
//         getInput(input); // Get user input
//         if (input[0] != NULL) { // If input not empty...
//             redir(input); // redirect ro relevant function
//         }
//         for (int i = 0; input[i] != NULL; i++) {
//             free(input[i]); // free allocated memory
//         }
//         updateRun(head); // check & update running processes
//     }
//     return 0;
// }

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
// #include <readline/history.h>
// #include "linked_list.h"

#define MAX_ARGS 128 // Define the maximum number of arguments

typedef struct Node {
    pid_t pid;
    char *path;
    int run;
    struct Node *next;
} Node;

// -----------------------------------------------

Node *addNode(Node *head, pid_t pid, char *path) {
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    node->pid = pid;
    node->path = strdup(path);

    if (node->path == NULL) {
        perror("Memory allocation failed");
        free(node);
        exit(EXIT_FAILURE);
    }

    node->run = 1;
    node->next = NULL;

    if (head == NULL) {
        return node;
    }

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = node;
    return head;
}

// Node *deleteNode(Node *head, pid_t pid) {
//     if (head == NULL) {
//         return NULL;
//     }

//     if (head->pid == pid) {
//         Node *temp = head->next;
//         free(head->path);
//         free(head);
//         return temp;
//     }

//     Node *prev = head;
//     Node *curr = head->next;

//     while (curr != NULL) {
//         if (curr->pid == pid) {
//             prev->next = curr->next;
//             free(curr->path);
//             free(curr);
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }

//     return head;
// }

Node *deleteNode(Node *head, pid_t pid) {
    if (head == NULL) {
        return NULL;
    }

    if (head->pid == pid) {
        Node *temp = head->next;
        free(head->path);  // Freeing the path
        free(head);        // Freeing the node
        head = NULL;       // Set head to NULL after freeing
        return temp;
    }

    Node *prev = head;
    Node *curr = head->next;

    while (curr != NULL) {
        if (curr->pid == pid) {
            prev->next = curr->next;
            free(curr->path);  // Freeing the path
            free(curr);        // Freeing the node
            curr = NULL;       // Set curr to NULL after freeing
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}


void printList(Node *node) {
    while (node != NULL) {
        printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
        node = node->next;
    }
}

Node *exists(Node *node, pid_t pid) {
    while (node != NULL) {
        if (node->pid == pid) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void updateRun(Node **head) {
    pid_t pid;
    int p_stat;

    while (1) {
        pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED);

        if (pid <= 0) {
            break;
        }

        Node *node = exists(*head, pid);

        if (node == NULL) {
            continue;
        }

        if (WIFSTOPPED(p_stat)) {
            printf("Process %d stopped.\n", pid);
            node->run = 0;
        }

        if (WIFCONTINUED(p_stat)) {
            printf("Process %d started.\n", pid);
            node->run = 1;
        }

        if (WIFSIGNALED(p_stat)) {
            printf("Process %d killed.\n", pid);
            *head = deleteNode(*head, pid);
        }

        if (WIFEXITED(p_stat)) {
            printf("Process %d terminated.\n", pid);
            *head = deleteNode(*head, pid);
        }
    }
}

// -----------------------------------------------

Node *head = NULL;

void bg(char **input) {
    pid_t pid = fork(); 
    if (pid < 0) { // Failed
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        if (execvp(input[1], &input[1]) == -1) { // Execute the specified program with arguments
            // perror("Execution failed");
            // exit(EXIT_FAILURE);
            printf("Execution failed\n");
        }
    } else {
        if (input[1] != NULL) { // Check if the command has an argument
            head = addNode(head, pid, input[1]); // Assuming input[1] contains the path to the executable
        }
        printf("Added process with PID %d to the list.\n", pid);
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
    Node *node = exists(head, pid);
    if (node != NULL) {
        head = deleteNode(head, pid); // Remove the node with the given PID
        printf("Process with PID %d killed and removed from the list.\n", pid);
    } else {
        printf("Process with PID %d is not in the list.\n", pid);
    }
}

void bglist() {
    if (head == NULL) {
        printf("The process list is empty.\n");
        return;
    }
    printf("Process list:\n");
    printList(head); // Print the linked list
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
    if (line && *line) { // Check if it's not null or empty
        // add_history(line); // Add input to history
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
    }
    free(line);
}

int main(int argc, char *argv[]) {
    // Error handling: CL args
    if (argc > 1) { // if args...
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1; // error
    }
    while(1){ // Inf loop
        char *input[MAX_ARGS+1]; // Holds user input
        getInput(input); // Get user input
        if (input[0] != NULL) { // If input not empty...
            redir(input); // redirect to relevant function
        }
        for (int i = 0; input[i] != NULL; i++) {
            free(input[i]); // free allocated memory
        }
        updateRun(&head); // check & update running processes
    }
    return 0;
}