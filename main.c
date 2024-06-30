#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "linked_list.h"
#include "bg.h"
#include "pstat.h"

#define MAX_ARGS 128

/*

main.c
-------------
Contains main loop for pman, with helper functions to process & respond to user input
- input: Holds command line arguments

*/

extern Node *head; // declare head node as extern

void genHelp() {
    printf("Available commands:\n");
    printf("  bg <path>      - Start a process in the background\n");
    printf("  bgkill <pid>   - Kill a background process\n");
    printf("  bgkill a       - Kill all background processes\n");
    printf("  bglist         - List all running background processes\n");
    printf("  bgstart <pid>  - Start a stopped background process\n");
    printf("  bgstop <pid>   - Stop a running background process\n");
    printf("  pstat <pid>    - Display statistics of a background process\n");
    printf("  q              - Quit pman\n");
}

// Redirect input to appropriate function
void redir(char **input) {
    if (input[0] == NULL) { // Error: No input
        printf("Invalid input, try 'h' for available commands.\n");
        return;
    }
    if (strcmp(input[0], "bg") == 0) bg(input);
    else if (strcmp(input[0], "bgkill") == 0 && !input[2]) bgkill(input[1]);
    else if (strcmp(input[0], "bglist") == 0 && !input[1]) bglist();
    else if (strcmp(input[0], "bgstart") == 0 && !input[2]) bgstart(input[1]);
    else if (strcmp(input[0], "bgstop") == 0 && !input[2]) bgstop(input[1]);
    else if (strcmp(input[0], "pstat") == 0 && !input[2]) pstat(input[1]);
    else if (strcmp(input[0], "h") == 0 && !input[1]) genHelp();
    else if (strcmp(input[0], "q") == 0 && !input[1]) exit(0);
    else printf("Invalid input, try 'h' for available commands.\n");
}

// Get user input
void getInput(char **input) {
    char *line = readline("pman> "); // read CL input
    if (line && strcmp(line, "")!=0) { // If not null or empty:
        add_history(line); // add input to history
        char *token = strtok(line, " "); // tokenize input
        int i = 0;
        while (token && i < MAX_ARGS) { // Tokenize input:
            input[i++] = strdup(token); // store token in args array
            token = strtok(NULL, " "); // get the next token
        }
        if (i == MAX_ARGS && token != NULL) {
            fprintf(stderr, "Error: Too many arguments\n");
            for (int j = 0; input[j] != NULL; j++) free(input[j]); // Free allocated memory
        }
        free(line);
    }
}

// Run pman
int main(int argc, char *argv[]) {
    if (argc > 1) { // Error: CL args
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1;
    }
    while(1){ // Inf loop
        char *input[MAX_ARGS+1]; // holds user input
        for (int i = 0; i <= MAX_ARGS; i++) input[i] = NULL; // null array
        getInput(input); // get user input
        redir(input); // redirect to relevant function
        for (int i = 0; input[i] != NULL; i++) free(input[i]); // free allocated memory
        update(); // check & update running processes
    }
}