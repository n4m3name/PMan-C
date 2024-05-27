#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "bg.h"
#include "pstat.h"
#include "help.h"

#define MAX_ARGS 10 // Define the maximum number of arguments

void redir(char *command, char **args) {
    if (strcmp(command, "bg") == 0) bg(args);
    else if (strcmp(command, "bgkill") == 0) bgkill(args);
    else if (strcmp(command, "bglist") == 0) bglist(args);
    else if (strcmp(command, "bgstart") == 0) bgstart(args);
    else if (strcmp(command, "bgstop") == 0) bgstop(args);
    else if (strcmp(command, "pstat") == 0) pstat(args);
    else if (strcmp(command, "h") == 0) gen_help();
    else if (strcmp(command, "q") == 0) exit(0); // Exit the program
    else printf("Invalid input, try 'h' for available commands.\n");
}

void run() {
    char *input, *args[MAX_ARGS + 1]; // Array to store the arguments, +1 for NULL terminator
    while (1) { // Infinite loop for continuous execution
        if ((input = readline("pman> ")) && *input) { // Read input and check if it's not empty
            add_history(input); // Add input to history
            char *token = strtok(input, " "); // Tokenize input
            int i = 0;
            while (token && i < MAX_ARGS) {
                args[i++] = token; // Store the token in the args array
                token = strtok(NULL, " "); // Get the next token
            }
            args[i] = NULL; // NULL terminate the array
            if (args[0]) redir(args[0], args); // Redirect command to appropriate function
            else printf("Invalid input, try 'h' for available commands.\n");
        }
        free(input); // Free memory allocated for input
    }
}

int main(int argc, char *argv[]) {
    // Error handling: CL args
    if (argc > 1) { // if args...
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1; // error
    }

    run(); // Start the pman
    return 0;
}


// void bgkill(char **args) {
//     pid_t pid = atoi(args[1]); // Assuming the second token is the PID
//     if (kill(pid, SIGKILL) == 0) {
//         printf("Process %d killed successfully.\n", pid);
//     } else {
//         perror("Failed to kill process");
//     }
// }

// gcc -o pman pman.c bg.c pstat.c help.c -lreadline