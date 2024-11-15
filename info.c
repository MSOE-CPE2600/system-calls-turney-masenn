/**
 * @file info.c
 * @brief File to get information about the current system
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 9
 * Name: Matthew Senn
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <math.h>
#include <stdint.h>

void getTime();
void getName();
void getSystemInfo();
void getProcessors();
void getPageSize();

#define SECS_IN_DAY (60 * 60 * 24) // Use parentheses for clarity

/**
 * - Current Time                           X
 * - System Network Name                    X
 * - Operating System Name                  X
 * - System Release and Version             X
 * - System Hardware Type                   X
 * - CPUs in the system                     X               
 * - Total Memory                           X
 * - Total amount of available memory       X
 */

int main(int argc, char* argv[]) {
    getTime();
    getName();
    getProcessors();
    getSystemInfo();
    getPageSize(); // Removed duplicate call to getProcessors
    return 0;
}

void getTime() {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        time_t seconds = ts.tv_sec;
        struct tm *local_time = localtime(&seconds);
        
        // Print the time in CST
        printf("Current CST time: %02d:%02d:%02d\n", 
               (local_time->tm_hour + 24) % 24, // Adjust for CST
               local_time->tm_min, 
               local_time->tm_sec);
    } else {
        perror("clock_gettime");
    }
}

void getName() {
    char hostname[256]; // Buffer to hold the hostname
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Host Name: %s\n", hostname);
    } else {
        perror("gethostname");
    }
}

void getSystemInfo() {
    struct utsname buf; // Struct containing system information
    if (uname(&buf) == 0) {
        printf("Network name: %s\n", buf.nodename);
        printf("Operating system: %s\n", buf.sysname);
        printf("Release: %s\n", buf.release);
        printf("Version: %s\n", buf.version);
        printf("Machine: %s\n", buf.machine);
    } else {
        perror("uname");
    }
}

void getProcessors() {
    printf("Number of Processors: %d\n", get_nprocs());
}

void getPageSize() {
    // Amount of memory expressed in pages. Page size is in bytes
    long int pages = sysconf(_SC_PHYS_PAGES);
    long int availablePages = sysconf(_SC_AVPHYS_PAGES);
    long int size = sysconf(_SC_PAGESIZE);
    
    printf("Total memory: %ld bytes\n", pages * size);
    printf("Available memory: %ld bytes\n", availablePages * size);
}
