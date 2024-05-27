#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "help.h" // Include the help header

#include "bg.h"
#include "pstat.h"


/*
#include "args.h"
#include "bg.h"
#include "bgkill.h"
#include "bglist.h"
#include "bgstartstop.h"
#include "pstat.h"
*/

/*
ToDo:
- [x] Start/test PMan input
- [x] Add 'help' (Do this later)
- [ ] Implement bg: forks programs
- [ ] Implement bg subprograms
- [ ] Implement pstat.c

*/

#define MAX_ARGS 10 // Define the maximum number of arguments

// void print_remaining_args(char **args) {
//     for (int i = 1; args[i] != NULL; i++) {
//         printf("Arg[%d]: %s\n", i, args[i]);
//     }
// }

// void bg(char **args) {
//     printf("BG\n");
//     print_remaining_args(args);
// }

// void bgkill(char **args) {
//     printf("BGKILL\n");
//     print_remaining_args(args);
// }

// void bglist(char **args) {
//     printf("BGLIST\n");
//     print_remaining_args(args);
// }

// void bgstart(char **args) {
//     printf("BGSTART\n");
//     print_remaining_args(args);
// }

// void bgstop(char **args) {
//     printf("BGSTOP\n");
//     print_remaining_args(args);
// }

// void pstat(char **args) {
//     printf("PSTAT\n");
//     print_remaining_args(args);
// }

// void bg() {
//     printf("BG\n");
// }

// void bgkill() {
//     printf("BGKILL\n");
// }

// void bglist() {
//     printf("BGLIST\n");
// }

// void bgstart() {
//     printf("BGSTART\n");
// }

// void bgstop() {
//     printf("BGSTOP\n");
// }

// void pstat() {
//     printf("PSTAT\n");
// }

// void gen_help() {
//     printf("Available commands:\n");
//     printf("  bg       - Start a program in the background\n");
//     printf("  bgkill   - Kill a background program\n");
//     printf("  bglist   - List all running background programs\n");
//     printf("  bgstart  - Start a stopped background program\n");
//     printf("  bgstop   - Stop a running background program\n");
//     printf("  pstat    - Display statistics of a background program\n");
//     printf("  q        - Quit the program\n");
// }

void redir(char *command, char **args) {
    if (strcmp(command, "bg") == 0) bg(args);
    else if (strcmp(command, "bgkill") == 0) bgkill(args);
    else if (strcmp(command, "bglist") == 0) bglist(args);
    else if (strcmp(command, "bgstart") == 0) bgstart(args);
    else if (strcmp(command, "bgstop") == 0) bgstop(args);
    else if (strcmp(command, "pstat") == 0) pstat(args);
    else if (strcmp(command, "h") == 0) gen_help(args);
    else if (strcmp(command, "q") == 0) exit(0); // Exit the program
    else printf("Invalid input, try 'h' for available commands.\n");
}

// void redir(char *command) {
//     if (strcmp(command, "bg") == 0) bg();
//     else if (strcmp(command, "bgkill") == 0) bgkill();
//     else if (strcmp(command, "bglist") == 0) bglist();
//     else if (strcmp(command, "bgstart") == 0) bgstart();
//     else if (strcmp(command, "bgstop") == 0) bgstop();
//     else if (strcmp(command, "pstat") == 0) pstat();
//     else if (strcmp(command, "h") == 0) help();
//     else if (strcmp(command, "q") == 0) exit(0); // Exit the program
//     else printf("Invalid input, try 'h' for available commands.\n");
// }

void run() {
    char *input;
    char *args[MAX_ARGS + 1]; // Array to store the arguments, +1 for NULL terminator
    while (1) { // Infinite loop for continuous execution
        input = readline("pman> "); // Read input
        if (input && *input) { // If input is not empty
            add_history(input); // Add input to history
            char *prog = strtok(input, " "); // Tokenize input
            int i = 0;
            while (prog && i < MAX_ARGS) {
                args[i++] = prog; // Store the token in the args array
                prog = strtok(NULL, " "); // Get the next token
            }
            args[i] = NULL; // NULL terminate the array
            if (args[0]) redir(args[0], args); // Redirect command to appropriate function
        }
        free(input); // Free memory allocated for input
    }
}

// void run() {
//     char *input;
//     while (1) { // Infinite loop for continuous execution
//         input = readline("pman> "); // Read input
//         if (input && *input) { // If input is not empty
//             add_history(input); // Add input to history
//             char *prog = strtok(input, " "); // Tokenize input
//             if (prog) redir(prog); // Redirect token to appropriate function
//         }
//         free(input); // Free memory allocated for input
//     }
// }

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


// gcc -o pman pman.c help.c -lreadline
