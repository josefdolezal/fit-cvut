#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;
  int status;

  /* Spawn a child process running the "ls" command.  */

  /* Duplicate this process.  */
  child_pid = fork ();
  switch( child_pid ) {
    case -1:  /* Error */
      fprintf(stderr,"Error: fork()");
      exit(EXIT_FAILURE);
    case 0:   /* Children code */
      execlp("sleep", "sleep", "30", (char *) NULL);
      fprintf(stderr,"Error: execlp()");
      exit(EXIT_FAILURE); 
    default:  /* Parent code */
      wait(&status);   
      printf("done with main program\n"); 
   };
  return EXIT_SUCCESS;
}
