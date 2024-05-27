#include <stdio.h>
#include "pstat.h"

void ps_print_remaining_args(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("Arg[%d]: %s\n", i, args[i]);
    }
}

void pstat(char **args) {
    printf("PSTAT\n");
    ps_print_remaining_args(args);
}
