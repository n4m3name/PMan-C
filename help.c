#include <stdio.h>
#include "help.h"

void gen_help() {
    printf("Available commands:\n");
    printf("  bg       - Start a program in the background\n");
    printf("  bgkill   - Kill a background program\n");
    printf("  bglist   - List all running background programs\n");
    printf("  bgstart  - Start a stopped background program\n");
    printf("  bgstop   - Stop a running background program\n");
    printf("  pstat    - Display statistics of a background program\n");
    printf("  q        - Quit the program\n");
}
