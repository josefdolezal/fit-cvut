#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Parametry predane funci vlakna
 */
typedef struct TThreadArg
{
  char character;  /* jaky znak tisknout */
  int  count;      /* kolikrat.  */
  int  id;         /* identifikace vlakna */
} TTHREADARG;

/* Funkce vlakna zobrazi zadany pocet krat zadany znak.
 * Pocet a znak jsou predane jako parametry.
 */
void * printThread ( void * parameters )
{
  /* pretypovanui parametru */
  TTHREADARG * p = (TTHREADARG*) parameters;
  int i;

  for (i = 0; i < p->count; ++i)
    fputc (p->character, stdout);
  printf ( "\nThread %d: done.\n", p -> id );
  return NULL;
}

int main ( int argc, char * argv [] )
{
  pthread_t  thr1;
  pthread_t  thr2;
  TTHREADARG arg1;
  TTHREADARG arg2;
  int rc;

  /* prvni vlakno vypise 10000x znak 'x'
   */
  arg1 . character = 'x';
  arg1 . count = 10000;
  arg1 . id  = 1;
  rc = pthread_create (&thr1, NULL, &printThread, (void*)&arg1);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    return(EXIT_FAILURE);
  }

  /* druhe vlakno vypise 30000x znak 'o'
   */
  arg2 . character = 'o';
  arg2 . count = 30000;
  arg2 . id  = 2;
  rc = pthread_create (&thr2, NULL, &printThread, (void*)&arg2 );
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    return(EXIT_FAILURE);
  }
 
  /* Cekame na prvni vlakno. Navratova hodnota vracena z vlakna nas nezajima,
   * nepredavame proto druhy parametr (promennou, kam by se vysledek zapsal).
   * NULL hodnota se chape jako "neni podstatne, out parametr nezapisuj".
   * Ceka se blokujicim zpusobem (funkce se vrati az po dobehnuti vlakna,
   * na ktere cekame), vlastni cekani nespotrebovava cas CPU.
   *
   * Implementace neni zcela korektni, vlakno ma nastavene vychozi atributy,
   * ktere nemusi umoznovat pouziti pthread_join.
   */
  pthread_join (thr1, NULL);
  /* Cekani na druhe vlakno
   */
  printf ( "\nMain: the first thread has finished.\n" );

  pthread_join (thr2, NULL);
  /* Zde uz opet bezi pouze hlavni vlakno, prostredky alokovane pro
   * predchozi vlakna byly uvolnene.
   */

  printf("Main: Both threas have finished.\n");
  return EXIT_SUCCESS;
}

