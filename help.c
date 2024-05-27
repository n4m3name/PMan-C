#include <stdio.h>

void gen_help() {
    printf("Available commands:\n");
    printf("  bg       - Run a program in the background\n");
    printf("  bgkill   - Kill a background process\n");
    printf("  bglist   - List all background processes\n");
    printf("  bgstart  - Start a stopped background process\n");
    printf("  bgstop   - Stop a running background process\n");
    printf("  pstat    - Display process statistics\n");
    printf("  h        - Display this help message\n");
    printf("  q        - Quit the program\n");
}
