#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to copy contents of file2 to file1
void copyContents( char* file1 , char* file2 , char* mode ) {
FILE *fp1, *fp2;

// Open file
    fp1 = fopen(file1, mode);
    if (fp1 == NULL)
    {
        if(debug) printf("Cannot open file %s for writing \n", file1);
        return ;
    }

   fp2 = fopen(file1, "r");
    if (fp2 == NULL)
    {
        if(debug) printf("Cannot open file %s for writing \n", file2);
        return;
    }

    // Read contents from file
    char c = fgetc(fp2);
    while (c != EOF)
    {
        fprintf(fp1,"%c", c);
        c = fgetc(fp2);
    }

    fclose(fp1);
   fclose(fp2);

}

// This function implements path command
void path() {
   char cwd_str[500];
   // print current working directory
   if (getcwd(cwd_str, sizeof(cwd_str)) != NULL) {
       printf("Current directory : %s \n", cwd_str);
   } else {
       perror("getcwd() error");
       //return ;
   }

       // print contents of file t2.txt
       printf("Contents of t2.txt : \n") ;
       printFile("t2.txt");
       // rename t2.txt to path-info.txt
       file_rename("t2.txt","path-info.txt");
       // copy contents of tree.txt and path.txt to t3.txt
       copyContents("t3.txt","tree.txt","w");
       copyContents("t3.txt","path.txt","a");
       file_rename("t3.txt","log.txt");
       if ( remove("tree.txt") == 0 )
           if(debug) printf(" In Path Command : deleted tree.txt successfully \n");
       else
           if(debug) printf(" In Path Command: could not delete tree.txt \n");

       if ( remove("path.txt") == 0 )
           if(debug) printf(" In Path Command : deleted path.txt successfully \n");
       else
           if(debug) printf(" In Path Command: could not delete path.txt \n");


}
