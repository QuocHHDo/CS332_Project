#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Format of directory entries
#include <errno.h> 
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *argls[] = {"ls", "-l", NULL};

    DIR *dfd; // DIR is a type representing a directory stream. dfd stands for directory file descriptor. 
    struct dirent *dp; // dp stands for directory pointer
 
    if(!dfd) // If directory is not found 
    {
        fprintf(stderr, "Unable to open current directory: %s\n", strerror(errno));      
        exit(1);
    }
    else 
    {
        dfd = opendir("."); // Open up current directory
    }

    if (errno) // If directory cannot be read
    {
        fprintf(stderr, "Unable to read current directory: %s\n", strerror(errno));        
        exit(1); 
    }
    else 
    {
        printf("All content of the current directory: \n\n");
        // while ((dp = readdir(dfd))) // Read all the files in the directory 
        // {
        //     puts (dp -> d_name);
        // }

        execvp(argls[0], argls);

    }

    closedir(dfd); // Close the current directory file and frees the space

    char input[32]; 
    
    printf("\nHit the return key again to terminate the shell.\n"); 
    fgets(input,sizeof(input), stdin); //Take the user input

    if(input[0]=='\n') //If user pressed only the return key
    {
        printf("Shell has been successfully terminated.\n"); 
    }
    

    return 0; 
}