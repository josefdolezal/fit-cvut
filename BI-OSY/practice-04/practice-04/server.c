#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
  char c;
  int shmid;
  key_t key;
  char *shm, *s;

  /*
   * We'll name our shared memory segment
   * "5678".
   */
  key = 5679;

  /*
   * Create the segment.
   * 0700 - pristupova prava
   */
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0700)) < 0) {
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
   * Now put some things into the memory for the
   * other process to read.
   */
  s = shm;

  for (c = 'a'; c <= 'z'; c++)
    *s++ = c;
  *s = 0;

  /*
   * Finally, we wait until the other process 
   * changes the first character of our memory
   * to '*', indicating that it has read what 
   * we put there.
   */
  while (*shm != '*')
    sleep(1);

   /* Now we dettach the segment.
   */
  if ( shmdt(shm) < 0 ) {
    perror("shmdt");
    exit(1);
  }

   /* Now we deallocate the segment.
   */
     if ( shmctl(shmid, IPC_RMID, 0 ) < 0 ) {
       perror("shmctl");
       exit(1);
     }

   return EXIT_SUCCESS;
}
