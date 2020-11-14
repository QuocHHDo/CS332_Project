#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h> 

int main ()
{
    DIR *dirp; 
    struct dirent *dp; 

    dirp = opendir(".");
    if(!dirp)
    {
        perror("opendir()");
        exit(1);
    }
    while ((dp = readdir(dirp)))
    {
        puts (dp -> d_name);
    }
    if (errno)
    {
        perror("readdir()");
        exit(1); 
    }
}