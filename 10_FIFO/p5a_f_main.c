/* Directory calls */
/* opendir, readdir, closedir */
/* struct dp { d_name };*/
/* Stat 11.1 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define COMMAND_ARG   2
#define PATH_WAY      1
#define SIZE          2000


int main(int argc, char *argv[])
{
  DIR *dirptr;               //store path_way
  struct dirent *dp;         //struct dirent pointer         
  char temp_name[4000];      //store file name

  int cd;                      //change dir
  
  struct stat statbuf;       //struct stat pointer  
  char t[SIZE] = "";          //time
 
  /* Command line check */
  if(argc != COMMAND_ARG)
    {
      fprintf(stderr, "Usage: %s dirname\n", argv[0]);
      exit(1);
    }
  
  /* Open the specified directore */
  if((dirptr = opendir(argv[PATH_WAY])) == NULL)
    {
      fprintf(stderr, "Could not open directore %s\n", argv[PATH_WAY]);
      exit(1);
    }
  
  /* Change directory */
  if((cd = chdir(argv[PATH_WAY])) == -1)
    {
      fprintf(stderr, "Could not change directore %s\n", argv[PATH_WAY]);
      exit(-1);
    }
  
  
  /* Go through the directory entries and print file names. */
  while((dp = readdir(dirptr)) != NULL)
    {
      strcpy(temp_name, dp->d_name);
      if(temp_name[0] == '.')
	{
	  if(strcmp(dp->d_name, ".") == 0)
	    {
	      continue;      //go begining at loop
	    }
	  if(strcmp(dp->d_name, "..") == 0)
	    {
	      continue;      //go begining at loop
	    }
	  else
	    {
	      printf("\t%s", dp->d_name); fflush(stdout);
	      /* Open stat */
	      if(stat(temp_name, &statbuf) == -1)
		{
		  printf("  Could not get stat on file %s\n", temp_name);
		  fflush(stdout);
		  continue;                        
		}
	      printf("\t\t%ld\t", statbuf.st_size); fflush(stdout);
	      strftime(t, SIZE, "%b %d %Y", localtime(&statbuf.st_mtime));
	      printf("%s\n", t); fflush(stdout); 
	    }
	}
     }//end of while loop
  
  /* Close the directory and stop */
  closedir(dirptr);
  
  return 0;
}
