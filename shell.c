
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int child, child2;
	char* args[1024];
	char buffer[1024];
	int count;
	
	while(true){

        /*
         * Seperate arguments using " "
         */
		char delimiter[2] = " ";
		printf("<shell>: ");

        /* 
		 * Reads size0f(buffer)-1 characters from the file stream stdin
         * Stores them in the array buffer
		 */ 
		fgets(buffer, sizeof(buffer), stdin);

        /* strtok: Breaks a string into a series of tokens based on a delimiter
		 * Add each token to the array from command line to populate list of arguments
		 */
		args[count] = strtok(buffer, delimiter);
		while (args[count] != NULL){
			count++;
			args[count] = strtok(NULL, delimiter);
		}

		/*
         * remove newline char on final argument
         */ 
		args[count-1][strlen(args[count- 1 ]) - 1] = '\0';


        /*
         * Check if user wants to quit
         */ 
		
		if (strcmp(args[0], "exit" ) == 0){
			execv("exit", &argv[0]);
			continue;	
		}

		if (strcmp(args[0], "tree" ) == 0){
			child2 = fork();
			if(child2 == 0){
				execv("tree", &argv[0]);
				exit(0);
			}
			wait(NULL);
			
			continue;
		}

		if (strcmp(args[0], "list" ) == 0){
			child2 = fork();
			if(child2 == 0){
				execv("list", &argv[0]);
				exit(0);
			}
			wait(NULL);
		}
		

		if (strcmp(args[0], "path" ) == 0){
			child2 = fork();
			if(child2 == 0){
				execv("path", &argv[0]);
				exit(0);
			}
			wait(NULL);
		}



        /*
         * Create child processes to execute commands
         */ 
		child = fork();
		if (child == -1){
			perror("Could not fork child process");
			exit(-1);
		}
		else if(child == 0){
			execvp(args[0], args);
			printf("Command not found\n");
			exit(0);
		}
		
        /*
         * Reset command line for next set of arguments =)
         */ 
		wait(NULL);
		count = 0;
		printf("\n");
	}

	return 0;
}
