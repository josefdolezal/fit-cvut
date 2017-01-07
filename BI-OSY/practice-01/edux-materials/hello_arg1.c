#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 8

/* Program obsahuje chybu. Mel by zobrazit pozdrav v 8 intergalaktickych jazycich (tedy ne cesky),
 * ale pozdravi 8x pouze pouze cesky. Opravte tuto chybu - udelejte z nej polyglota!
 */

char *messages[NUM_THREADS + 1] = 
{
   "English: Hello World!",
   "French: Bonjour, le monde!",
   "Spanish: Hola al mundo",
   "Klingon: Nuq neH!",
   "German: Guten Tag, Welt!",
   "Russian: Zdravstvytye, mir!",
   "Japan: Sekai e konnichiwa!",
   "Latin: Orbis, te saluto!",
   "Cesky: Ahoj svete!"
};


void * helloThread ( void * threadid )
{
  int id_ptr, taskid;

  sleep(1);
  id_ptr = (int)(uintptr_t)threadid;
  taskid = id_ptr;
  printf("Thread %d: %s\n", taskid, messages[taskid]);
  return(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc, t;

  for(t=0; t <= NUM_THREADS;t++) {
    printf("Main: Creating thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, helloThread, (void *)(uintptr_t)t ); /* nahrazeni pointeru */
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      return (EXIT_FAILURE);
    }
  }
  /* Toto neni standardni zpusob ukonceni programu s vlakny.
   */
  pthread_exit(NULL);
  return ( 0 ); /* ale zde je to zbytecne - nedosazitelne */
}

