#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
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
- [ ] Add 'help'
- [ ] Implement bg: forks programs
- [ ] Implement bg subprograms
- [ ] Implement pstat.c

*/

void bg() {
    printf("BG\n");
}

void bgkill() {
    printf("BGKILL\n");
}

void bglist() {
    printf("BGLIST\n");
}

void bgstart() {
    printf("BGSTART\n");
}

void bgstop() {
    printf("BGSTOP\n");
}

void pstat() {
    printf("PSTAT\n");
}

void redir(char *command) {
    if (strcmp(command, "bg") == 0) {
        bg();
    } else if (strcmp(command, "bgkill") == 0) {
        bgkill();
    } else if (strcmp(command, "bglist") == 0) {
        bglist();
    } else if (strcmp(command, "bgstart") == 0) {
        bgstart();
    } else if (strcmp(command, "bgstop") == 0) {
        bgstop();
    } else if (strcmp(command, "pstat") == 0) {
        pstat();
    } else if (strcmp(command, "q") == 0) {
        exit(0); // Exit the program
    } else {
        printf("Invalid input, please try again.\n");
    }
}

void run() {
    char *input;
    while (1) { // Infinite loop for continuous execution
        input = readline("pman> "); // Read input
        if (input != NULL && *input != '\0') { // If input is not empty
            add_history(input); // Add input to history
            char *token = strtok(input, " "); // Tokenize input
            while (token != NULL) {
                redir(token); // Redirect token to appropriate function
                token = strtok(NULL, " "); // Get next token
            }
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
