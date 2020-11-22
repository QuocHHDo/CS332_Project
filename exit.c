#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

int main(char **args)
{
     pid_t  pid;
     int status;               
     char input[32]; // User input 
     char *argls[] = {"ls", "-l", NULL};
 
     while(true) {
          
          pid = fork(); // Fork a child process which returns the PID of it
          
          if (pid < 0) { // If PID is less than 0, then fork failed 
               fprintf(stderr, "Error forking child process: %s\n", strerror(errno));  
               exit(1);
          }
          else if (pid == 0){ // If PID is zero, then fork succeeded 
               printf("All content of the current directory: \n");
               
               execvp(argls[0], argls);  // Read all the files in the directory 
          } 
          else // For the parent process
          {                                  
               while (wait(&status) != pid);
               printf("\nHit the return key again to terminate the shell.\n");    
          }      
          wait(NULL);     

          do {  // Keep asking user for input until user input next line 
               fgets(input,sizeof(input), stdin);
          } while (input[0] != '\n'); 

          printf("Shell has been successfully terminated.\n"); // Print 
          return 0; 
     }    
}
