#include <stdio.h>
#include "bg.h"

void print_remaining_args(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("Arg[%d]: %s\n", i, args[i]);
    }
}

void bg(char **args) {
    printf("BG\n");
    print_remaining_args(args);
}

void bgkill(char **args) {
    printf("BGKILL\n");
    print_remaining_args(args);
}

void bglist(char **args) {
    printf("BGLIST\n");
    print_remaining_args(args);
}

void bgstart(char **args) {
    printf("BGSTART\n");
    print_remaining_args(args);
}

void bgstop(char **args) {
    printf("BGSTOP\n");
    print_remaining_args(args);
}


/*

        if (access(input, X_OK) == -1) { // check if valid
            // Program/process does not exist or is not executable
            printf("Error: Program or process '%s' does not exist or is not executable.\n", input);
        } else {
            // Program/process exists and is executable
            // Process input (you'll need to implement this part)
            // For example:
            // parse_input(input);
        }

*/



