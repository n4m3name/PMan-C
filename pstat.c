#include "pstat.h"

/*

pstat.c
-------------
Contains pstat & helper functions,
see pstat.h for concise summary of functions.
- sPid: process id as command-line argument (string)
- pid, comm, state, utimeRaw, stimeRaw, rss: Basic process info as found in /proc/.../stat file
- v_ctxt, nv_ctxt: Volutary ctxt switches & nonvoluntary ctxt switches as found in /proc/.../status file

*/

// Validate input PID, convert to int
int validateInputPid(char *sPid) {
    pid_t pid; 
    if (!sPid) { fprintf(stderr, "Usage: pstat <pid>\n"); return 0; } // Error: No input provided
    pid = atoi(sPid); 
    if (pid == 0) { // Error: Invalid PID
        fprintf(stderr, "Invalid PID\n"); 
        return 0; 
    }
    return checkProcessExists(head, pid); // ensure only pid's added to list can be checked
}

// Read process information from /proc/[PID]/stat file
int readStatFile(pid_t pid, char *comm, char *state, unsigned long *utimeRaw, unsigned long *stimeRaw, long *rss) {
    char path[50]; 
    sprintf(path, "/proc/%d/stat", pid); // holds path
    FILE *file = fopen(path, "r"); 
    if (!file) { // Error: Failed to open stat file
        perror("Error"); 
        return 0; 
    }
    if (fscanf(file, "%*d (%[^)]) %c %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %*s %*s %ld %*s %*s \
                                    %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s", \
                                    comm, state, utimeRaw, stimeRaw, rss) != 5) { // Copy values from stat file to varibales, skip as needed. Error: copy failure
        perror("Error"); printf("Failed to read stat data for PID %d.\n", pid);
        fclose(file); return 0; 
    }
    fclose(file); return 1; // success
}

// Read context switch information from /proc/[PID]/status file
int readStatusFile(pid_t pid, unsigned long *v_ctxt, unsigned long *nv_ctxt) {
    char path[50]; 
    sprintf(path, "/proc/%d/status", pid); // copy path
    FILE *status_file = fopen(path, "r"); 
    if (!status_file) {
        perror("Error"); 
        return 0; 
    } // Error: Failed to open status file
    char line[256]; 
    while (fgets(line, sizeof(line), status_file)) { // Iterate over lines in file
        if (sscanf(line, "voluntary_ctxt_switches: %lu", v_ctxt) == 1 || \
            sscanf(line, "nonvoluntary_ctxt_switches: %lu", nv_ctxt) == 1) // copy ctxt switches if found in line
            ; // do nothing
    }
    fclose(status_file); return 1; // success
}

// Run pstat & output results
void pstat(char *sPid) {
    if (!validateInputPid(sPid)) return; // Error: invalid input
    pid_t pid = atoi(sPid);
    char comm[256], state; 
    unsigned long utimeRaw, stimeRaw, voluntary_ctxt_switches = 0, nonvoluntary_ctxt_switches = 0; 
    long rss;
    if (!readStatFile(pid, comm, &state, &utimeRaw, &stimeRaw, &rss) || \
        !readStatusFile(pid, &voluntary_ctxt_switches, &nonvoluntary_ctxt_switches)) return; // Copy values from files, Error: failrure to copy values
    float utime = utimeRaw / 100.0, stime = stimeRaw / 100.0; // convert from clock to seconds
    printf("comm:\t%s\nstate:\t%c\nutime:\t%.2f seconds\nstime:\t%.2f seconds\nrss:\t%ld \
                    \nvoluntary ctxt switches:\t%lu\nnonvoluntary ctxt switches:\t%lu\n", \
            comm, state, utime, stime, rss, voluntary_ctxt_switches, nonvoluntary_ctxt_switches); // output info
}