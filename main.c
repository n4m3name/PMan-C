#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "linked_list.h"

#define MAX_ARGS 128 // Define the maximum number of arguments

Node* head = NULL;

void bg(char** input){
  	//Your code here;
    printf("BG\n");
}


void bglist(){
	//Your code here;
    printf("BGList\n");
}


void bgkill(char* str_pid){
	//Your code here
    printf("BGKill\n");
}


void bgstop(char* str_pid){
	//Your code here
    printf("BGStop\n");
}


void bgstart(char* str_pid){
	//Your code here
    printf("BGStart\n");
}


void pstat(char* str_pid){
	//Your code here
    printf("Pstat\n");
}

void update(){

}

void genHelp(){
    printf("Available commands:\n");
    printf("  bg       - Start a program in the background\n");
    printf("  bgkill   - Kill a background program\n");
    printf("  bglist   - List all running background programs\n");
    printf("  bgstart  - Start a stopped background program\n");
    printf("  bgstop   - Stop a running background program\n");
    printf("  pstat    - Display statistics of a background program\n");
    printf("  q        - Quit the program\n");
}

void redir(char** input) {
    if (strcmp(input[0], "bg") == 0) bg(input);
    else if (strcmp(input[0], "bgkill") == 0) bgkill(input[1]);
    else if (strcmp(input[0], "bglist") == 0) bglist();
    else if (strcmp(input[0], "bgstart") == 0) bgstart(input[1]);
    else if (strcmp(input[0], "bgstop") == 0) bgstop(input[1]);
    else if (strcmp(input[0], "pstat") == 0) pstat(input[1]);
    else if (strcmp(input[0], "h") == 0) genHelp();
    else if (strcmp(input[0], "q") == 0) exit(0); // Exit the program
    else printf("Invalid input, try 'h' for available commands.\n");
}

void getInput(char** input){
    char *line = readline("pman>");
    if (line && *line) { // Check if it's not null or empty
        add_history(line); // Add input to history
        char *token = strtok(line, " "); // Tokenize input
        int i = 0;
        while (token && i < MAX_ARGS) {
            input[i++] = strdup(token); // Store the token in the args array
            token = strtok(NULL, " "); // Get the next token
        }
        input[i] = NULL; // Null terminate array
        if (!input[0]) printf("Invalid input, try 'h' for available commands.\n");
    }
    free(line);
}

int main(int argc, char *argv[]) {
    // Error handling: CL args
    if (argc > 1) { // if args...
        fprintf(stderr, "Error: pman does not accept command-line arguments.\n");
        return 1; // error
    }
    while(1){ // Inf loop
        char *input[MAX_ARGS+1]; // Holds user input
        getInput(input); // Get user input
        if (input[0] != NULL) { // If input not empty...
            redir(input); // redirect ro relevant function
        }
        for (int i = 0; input[i] != NULL; i++) {
            free(input[i]); // free allocated memory
        }
        updateRun(); // check & update running processes
    }
    return 0;
}
