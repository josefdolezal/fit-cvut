#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

/* Nejake vypocty ve vlaknech, zde relativne "hodne" vypoctu.
 */
void * threadWork ( void * dummy )
{
  int i;
  double result = 0;
  for (i=0; i < 100000; i++) {
    result += 10.0 * rand () / RAND_MAX;
  }
  printf ("Thread %d: result = %f\n", (int) pthread_self(), result);
  return (NULL);
}

int main(int argc, char *argv[])
{
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc, t, status;

  /* Inicializujeme atribut vlakna, nastavime schopnot "byt pouzit s pthread_join()"
   */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(t=0;t<NUM_THREADS;t++) {
    rc = pthread_create(&thread[t], &attr, threadWork, NULL);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      return(EXIT_FAILURE);
    }
    printf("Main %d: Creating thread %d\n", (int) pthread_self(), (int) thread[t] );
  }

  /* Atributy vlaken uz dale nepotrebujeme - uvolnit
   */
  pthread_attr_destroy(&attr);

  /* Cekame na dokonceni
   */

  for(t=0;t<NUM_THREADS;t++) {
    rc = pthread_join(thread[t], (void **)&status);
    if (rc) {
      printf("ERROR return code from pthread_join() is %d\n", rc);
      return (EXIT_FAILURE);
    }
    printf("Main: Completed join with thread %d status= %d\n", (int) thread[t], status);
  }
  return ( EXIT_SUCCESS );
}

