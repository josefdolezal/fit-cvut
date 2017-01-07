/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ     27

int main()
{
  int shmid;
  key_t key;
  char *shm, *s;

  /*
   * We need to get the segment named
   * "5678", created by the server.
   */
  key = 5679;

  /*
   * Locate the segment.
   * Client si pamet nealokuje, pouze se k ni pripojuje
   */
  if ((shmid = shmget(key, SHMSZ, 0700)) < 0) {
    perror("shmget");
    exit(1);
  }

  /*
   * Now we attach the segment to our data space.
   */
  if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("shmat");
    exit(1);
  }

  /*
   * Now read what the server put in the memory.
   */
  for (s = shm; *s; s++)
    putchar(*s);
  putchar('\n');

  /*
   * Finally, change the first character of the 
   * segment to '*', indicating we have read 
   * the segment.
   */
  *shm = '*';

   /* Now we dettach the segment.
   */
  if ( shmdt(shm) < 0 ) {
    perror("shmdt");
    exit(1);
  }

  return EXIT_SUCCESS;
}
