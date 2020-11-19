// tree*: this new command will create a directory and call it Dir0. Then it will change the working
//directory to Dir0, and create three empty text files namely; t1.txt, t2.txt,and t3.txt, and one empty
//directory , called Dir1,inside it.
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

//function to make directory
int makeDirectory(char* directoryName){
    if (mkdir(directoryName, 0777) == -1){
        //if mkdir fails
        perror("Error while creating directory");
        return -1;
    }
    return 0;
}

//function to change directory
int changeDirectory(char* directoryName){
    if (chdir(directoryName) == -1){
        //if chdir fails
        perror("Failed to change directory: %s\n");
        return -1;  
    }   
    return 0;
}

//function to make files
int makeFile(char* fileName){
    FILE *fPtr;
    fPtr = fopen(fileName, "w");
    //if it fails to make a file
    if(fPtr == NULL){
        perror("Failed to create file");
        return 1;
    }
    fclose(fPtr);
    return 0;
}

int main(){
    char input[32]; 
    char* args[1024];

    while(true) {
        if(makeDirectory("Dir0") == -1){
            return -1;
        }

        if(changeDirectory("Dir0") == -1){
            return -1;
        }

        if(makeFile("t1.txt") == -1){
            return -1;
        }

        if(makeFile("t2.txt") == -1){
            return -1;
        }

        if(makeFile("t3.txt") == -1){
            return -1;
        }

        if(makeDirectory("Dir1") == -1){
            return -1;
        }

        fgets(input,sizeof(input), stdin);     
          if(input[0]=='\n')
          {
            args[0] = "run";
			execv("run", &args[0]);	
          }  
    }
}



