#include <stdio.h>
#include <unistd.h> // access()
#include <readline/readline.h> // input
#include <readline/history.h> // input
#include "args.h"
#include "bg.c"
#include "bgkill.h"
#include "bglist.c"
#include "bgstartstop.c"
#include "pstat.h"

int 

int main(int argc, char *argv[]) {
    // Error handling: CL args
    if (argc > 1) { // if args...
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1; // error
    }
    return 0;
    // bg (start processes)
    



}