#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 8

char *messages[NUM_THREADS] =
{
   "English: Hello World!",
   "French: Bonjour, le monde!",
   "Spanish: Hola al mundo",
   "Klingon: Nuq neH!",
   "German: Guten Tag, Welt!",
   "Russian: Zdravstvytye, mir!",
   "Japan: Sekai e konnichiwa!",
   "Latin: Orbis, te saluto!"
};

/* Vlaknu predavame vice ruznych parametru. Proto je zabalime do
 * struktury a predame odkaz na takovou strukturu.
 */
struct thread_data
{
  int   thread_id;
  int   sum;
  char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

/* Formalni tvar funkce vlakna ma parametr typu void * a navratovou hodnotu take typu void *.
 * Tento tvar je predepsany funkci pthread_create. Nam by se hodilo predavat paraemtry jineho
 * typu (zde konkretne struct thread_data *). Toho nelze dosahnout primo, lze to ale vyresit
 * pretypovanim. Vime, ze pri volani pthread_create predame ukazatel na pripravenou strukturu
 * struct thread_data. Tedy vime, ze ve funkci vlakna nepracujeme s obecnym void * ukazatelem,
 * ale s adresou priprave struktury struct thread_data *. Proto si predany ukazatel pretypujeme,
 * abychom s predanymi daty mohli pracovat. Vlastne jsme jen obesli typovy system C/C++.
 */

void * helloThread ( void * threadarg )
{
  struct thread_data *my_data;

  sleep(1);
  my_data = (struct thread_data *) threadarg;
  printf("Thread %d: %s  Sum=%d\n", my_data->thread_id, my_data->message, my_data->sum);
  return(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc, t, sum;

  sum=0;
  for(t=0;t<NUM_THREADS;t++) {
    sum = sum + t;
    thread_data_array[t].thread_id = t;
    thread_data_array[t].sum = sum;
    thread_data_array[t].message = messages[t];
    printf("Main: Creating thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, helloThread, (void *) &thread_data_array[t]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      return(EXIT_FAILURE);
    }
  }
  /* Stale jeste nestandardni ukonceni programu s thready
   */
  for( t = 0; t < NUM_THREADS; t++ ) {
    pthread_join(threads[t], NULL );
  }

  return ( 0 ); /* ale zde je to zbytecne - nedosazitelne */
}

