#include "bg.h"

/*

bg.c
-------------
Contains background process functions for pman,
see bg.h for concise summary of functions.
- input: command-line argument(s); executable, args
- sPid: process id as command-line argument (string)

*/

// Check if process exists in the list
int checkProcessExists(Node *head, pid_t pid) {
    Node *existingNode = exists(head, pid);
    if (!existingNode) { // Error: process does not exist
        fprintf(stderr, "Process with PID %d does not exist.\n", pid);
        return 0; // Process does not exist
    }
    return 1; // Process exists
}

// Start background process
void bg(char **input) {
    if (!input[1]) { // Error: no arg
        printf("Usage: bg <command>\n");
        return;
    }
    pid_t pid = fork(); // create child process
    if (pid == 0) { // Handle child:
        setpgid(0, 0); // set process group ID = parent (prevent interactivity, SIGTTN)
        execvp(input[1], &input[1]); // execute program w args
        perror("Execution failed"); // error: prev line failed
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Handle parent:
        printf("Started process %d\n", pid);
        addNode(&head, pid, input[1]); // add process to list
        sleep(1); // sleep for updateRun sync
    } else { // Error: ...
        perror("Failed to fork");
    }
}

// Kill background process by PID
void bgkill(char *sPid) {
    if (!sPid) { // Error: no input
        fprintf(stderr, "Usage: \n  bgkill <pid>\n  bgkill abgkill\n");
        return;
    }
    if (strcmp(sPid, "a") == 0) { // Kill all processes:
        Node *current = head, *prev; // copy head
        while (current) { // Iterate over list:
            kill(current->pid, SIGKILL); // kill process
            prev = current, current = current->next; // move cur to next
            deleteNode(&head, prev->pid); // remove node
        }
        printf("All active processes killed.\n");
        return;
    }
    pid_t pid = atoi(sPid); // convert input to PID
    if (!pid) { // Error: invalid pid
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if (!checkProcessExists(head, pid)) return;
    if (kill(pid, SIGKILL)) perror("Execution failed"); // kill process, print error if kill fails
    else sleep(1); // sleep for updateRun sync
    deleteNode(&head, pid); // remove node with given PID from list
    printf("Process with PID %d killed and removed from the list.\n", pid); // print status
}

// List running processes
void bglist() {
    if (!head) { // Error: empty list
        printf("The process list is empty.\n");
        return;
    }
    printList(head); // print list
}

// Stop background process by PID
void bgstop(char *sPid) {
    if (!sPid) { // Error: no input
        fprintf(stderr, "Usage: bgstop <pid>\n");
        return;
    }
    pid_t pid = atoi(sPid); // convert input to PID
    if (!pid) { // Error: invalid pid
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if (!checkProcessExists(head, pid)) return;
    if (kill(pid, SIGSTOP)) perror("Execution failed"); // stop process, print error if stop fails
    else sleep(1); // sleep for updateRun sync
}

// Resume background process by PID
void bgstart(char *sPid) {
    if (!sPid) { // Error: no input
        fprintf(stderr, "Usage: bgstart <pid>\n");
        return;
    }
    pid_t pid = atoi(sPid); // convert input to PID
    if (!pid) { // Error: invalid PID
        fprintf(stderr, "Invalid PID\n");
        return;
    }
    if (!checkProcessExists(head, pid)) return;
    if (kill(pid, SIGCONT)) perror("Execution failed"); // resume process, print error if resume fails
    else sleep(1); // sleep for updateRun sync
}