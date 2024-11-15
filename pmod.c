/** 
 * @file pmod.c
 * @brief Demonstrates process priority manipulation and sleep functionality.
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Process Management
 * Name: Your Name
 * 
 * Algorithm:
 * - Retrieve the current process ID and priority.
 * - Increase the process priority.
 * - Sleep for a specified duration.
 * - Exit gracefully.
 */
#include <unistd.h> 
#include <stdio.h>
#include <sys/resource.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int pid = getpid();
    int priority = getpriority(PRIO_PROCESS,pid);
    printf("PID: %d with priority %d\n",pid,priority);
    nice(10);
    struct timespec time;
    time.tv_sec = 1; 
    time.tv_nsec = 837272638; 
    if(!nanosleep(&time,NULL)){
        printf("Goodbye! Exiting.\n");
        exit(1);
    } else {
        printf("Could not sleep!\n");
    }

    return 0;
}