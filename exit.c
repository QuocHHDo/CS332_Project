#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>


int main()  
{
     pid_t  pid;
     int status;               
     char *argv[64];              /* the command line argument      */
     char input[32]; 
     char *argls[] = {"ls", "-l", NULL};
       
     while(true) {

          pid = fork();
          
          if (pid < 0) {     /* fork a child process           */
               printf("*** ERROR: forking child process failed\n");
               exit(1);
          }
          else if (pid == 0) 
          {          /* for the child process:         */
               printf("All content of the current directory: \n\n");
               execvp(argls[0], argls);       /* execute the command  */  
          } 
          else 
          {                                  /* for the parent:      */
               while (wait(&status) != pid);
               printf("\nHit the return key again to terminate the shell.\n");    
          }      
          wait(NULL);     

          do { 
               fgets(input,sizeof(input), stdin);
          } while (input[0] != '\n'); 

          printf("Shell has been successfully terminated.\n");
          return 0; 
     }    
}
