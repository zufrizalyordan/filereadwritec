/*
  15 Apr 2014
  Author : Zufrizal Yordan
  Desc : get files in subfolder, write the names to a text file without the file extension
*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

char *remove_ext (char* mystr, char dot, char sep) {
  char *retstr, *lastdot, *lastsep;

  // Error checks and allocate string.
  if (mystr == NULL)
    return NULL;
  if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
    return NULL;

  strcpy (retstr, mystr);
  lastdot = strrchr (retstr, dot);
  lastsep = (sep == 0) ? NULL : strrchr (retstr, sep);

  if (lastdot != NULL) {

    if (lastsep != NULL) {
      if (lastsep < lastdot) {
        *lastdot = '\0';
      }
    } else {
      *lastdot = '\0';
    }
  }

  return retstr;
}

int main(){
  DIR *dp;
  struct dirent *ep;
  dp = opendir ("Square Airline logos/"); // folder where you want to read the contents

  char *s;

  FILE *f = fopen("file.txt", "w+");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  if (dp != NULL)
  {
    while (ep = readdir (dp)){
      s = remove_ext (ep->d_name, '.', '/'); // remove the file extension
      if (strlen(s) > 1){

        if (f != NULL){
          fprintf(f, "%s, ", s); // write to file
        }

        free (s);
      }
    };
    (void) closedir (dp);
    printf("================\n");
    printf("File is written.\n");
    printf("================\n");
  }
  else
    perror ("Couldn't open the directory");

  return 0;
}

