/**
 * @file pinfo.c
 * @brief File to get information about the current or specified process
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 9
 * Name: Matthew Senn
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h> 
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int pid;

    if (argc > 1) {
        char *err;
        pid = strtol(argv[1], &err, 10); // Convert to int
        if (*err != '\0') { // Check if conversion was successful
            printf("Invalid Process ID\n");
            exit(1);
        }
    } else {
        pid = getpid(); // Get current process ID
    }

    printf("Current process PID: %d\n", pid); 

    int priority = getpriority(PRIO_PROCESS, pid);
    printf("Priority: %d\n", priority);

    int schedule = sched_getscheduler(pid);
    printf("Policy: ");
    if (schedule == SCHED_OTHER) {
        printf("SCHED_OTHER\n");
    } else if (schedule == SCHED_FIFO) {
        printf("SCHED_FIFO\n");
    } else if (schedule == SCHED_RR) {
        printf("SCHED_RR\n");
    } else if (schedule == SCHED_BATCH) {
        printf("SCHED_BATCH\n");
    } else if (schedule == SCHED_IDLE) {
        printf("SCHED_IDLE\n");
    } else {
        printf("Unknown scheduling policy\n");
    }

    return 0;
}
