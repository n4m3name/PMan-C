#include <stdio.h>
#include "pstat.h"

void print_remaining_args(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("Arg[%d]: %s\n", i, args[i]);
    }
}

void pstat(char **args) {
    printf("PSTAT\n");
    print_remaining_args(args);
}
