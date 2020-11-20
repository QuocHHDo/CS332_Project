#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// This function is used to copy contents of file2 to file1
void copyContents( char* file1 , char* file2 , char* file3 ) {
  FILE *fp1 = fopen(file1, "r");
  FILE *fp2 = fopen(file2, "r");

  // Open file to store the result
  FILE *fp3 = fopen(file3, "w");
  char c;
  if (fp1 == NULL || fp2 == NULL || fp3 == NULL){
    puts("Could not open files");
    exit(0);
  }
  // Copy contents of first file to file3.txt
  while ((c = fgetc(fp1)) != EOF)
  fputc(c, fp3);

  // Copy contents of second file to file3.txt
  while ((c = fgetc(fp2)) != EOF)
  fputc(c, fp3);

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
}

void file_rename( char* oldFilename, char* newFilename) {
  int ret = rename(oldFilename, newFilename);

  if(!ret){
    printf("File name changed successfully %s to %s \n", oldFilename , newFilename);
  }
  else{
    perror("Error");
  }
}

// This function implements path command
int main() {
  FILE * fptr;
  char ch;
  char cwd_str[500];
  const char *directory;
  // print current working directory
  if (getcwd(cwd_str, sizeof(cwd_str)) != NULL) {
    printf("Current directory : %s \n", cwd_str);
  }
  else {
    perror("getcwd() error");
  }
  fptr = fopen("Dir0/t2.txt", "a");

   // check for file opening
  if(fptr == NULL){
    //Unable to open file hence exit
    printf("Error writing to t2.txt\n");
    exit(1);
  }
  else{
    fprintf(fptr,"%s\n", cwd_str);
  }

  fclose(fptr);

  // rename t2.txt to path-info.txt
  file_rename("Dir0/t2.txt","Dir0/path-info.txt");
  copyContents("Dir0/tree.txt","Dir0/path-info.txt","Dir0/t3.txt");
  file_rename("Dir0/t3.txt","Dir0/log.txt");

  if (remove("Dir0/tree.txt") == 0)
    printf(" In Path Command : deleted tree.txt successfully \n");
  else
    printf(" In Path Command: could not delete tree.txt \n");

  if (remove("Dir0/path-info.txt") == 0)
    printf(" In Path Command : deleted path-info.txt successfully \n");
  else
    printf(" In Path Command: could not delete path.txt \n");
}
