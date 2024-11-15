/**
 * @file info.c
 * @brief gets info about a provided file on the command line
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 9
 * Name: Matthew Senn
 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/**
 * File Type                    X
 * Permissions                  X
 * Owner of the file--id        X
 * file size                    X
 * date of last modification    X
 */

int main(int argc, char* argv[])
{   
    if(argc < 2){
        printf("Insufficient arguments, exiting!\n");
        return -1;
    }
    struct stat stat_buf;
    if(stat(argv[1],&stat_buf)){
        printf("Could not get file %s info. Exiting!\n",argv[1]);
        return -1;
    }
    int mode = stat_buf.st_mode;
    printf("%d\n",mode);
    if (S_ISREG(mode)) printf("Regular file\n");
    else if (S_ISDIR(mode)) printf("Directory\n");
    else if (S_ISCHR(mode)) printf("Character device\n");
    else if (S_ISBLK(mode)) printf("Block device\n");
    else if (S_ISFIFO(mode)) printf("FIFO (named pipe)\n");
    else if (S_ISLNK(mode)) printf("Symbolic link\n");
    else if (S_ISSOCK(mode)) printf("Socket\n");

    printf("File permissions: ");
    if(S_IRUSR & mode)printf("Read | ");  
    if(S_IWUSR & mode)printf("Write | ");
    if(S_IXUSR & mode)printf("Exectue | ");
    if(S_IRGRP & mode)printf("Read Group | ");
    if(S_IWGRP & mode)printf("Write Group | ");
    if(S_IXGRP & mode)printf("Execute Group | ");
    if(S_IROTH & mode)printf("Read Other | ");
    if(S_IWOTH & mode)printf("Write Other | ");
    if(S_IXOTH & mode)printf("Execute Other | ");
    printf("\n");

    printf("Owner: %u\n",stat_buf.st_uid);
    printf("Size: %ld\n",stat_buf.st_size);
    printf("Modified at: %s", ctime(&stat_buf.st_mtime));
    return 0;
}