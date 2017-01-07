#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t g_Mtx;
int             g_Sum;


typedef struct TThrArg 
 {
   int        m_Max;
   int        m_Num;
   pthread_t  m_ThrID;
 } TTHRARG;
 
/* Funkce vlakna - vypise cisla v danem rozsahu. Parametry dostane 
 * jako netypovy ukazatel void *. Protoze vlakno vytvarime a vime,
 * ze tento netypovy ukazatel ve skutecnosti ukazuje na nami pripravenou
 * strukturu TTHRARG, pretypujeme tento ukazatel a pak pomoci typovaneho
 * ukazatele data pracujeme s predanymi hodnotami.
 */
void * thrFunc ( void * arg )
 {
   int i;
   int c = 0;

   TTHRARG  * data = (TTHRARG *)arg;
   
   for ( i = 0; i < data -> m_Max; i ++ )
    c += i+1;

   pthread_mutex_lock( &g_Mtx );
   g_Sum += c;
   pthread_mutex_unlock( &g_Mtx );

   return ( NULL );
 }

int main ( int argc, char * argv [] )
 {
   TTHRARG      * arg;
   pthread_attr_t thrAttr;
   int            i, thr;
   void         * dummy;
   g_Sum = 0;

   /* Vytvarime vlakno pro kazdy parametr z prikazove radky
    */
   thr = argc - 1;
   if ( thr <= 0 )
    {
      printf ( "Usage: %s n1 [n2 [n3 [...]]]\n", argv[0] );
      return ( 1 );
    }

   /* Pole parametru pro vlakna. 
    */
   pthread_mutex_init( &g_Mtx, NULL );

   arg = (TTHRARG *) malloc ( thr * sizeof ( *arg ) );

   for ( i = 0; i < thr; i ++ )
    {
      if ( sscanf ( argv[i+1], "%d", &arg[i] . m_Max) != 1 )
       {
         free ( arg );
         printf ( "Invalid argument %d\n", i + 1 );

         pthread_mutex_destroy( &g_Mtx );
         return ( 1 );
       }
      arg[i] . m_Num = i;
    }
 
   /* Atributy vlakna (ciste reseni, na vlakno lze cekat pomoci pthread_join). 
    */ 
   pthread_attr_init ( &thrAttr );
   pthread_attr_setdetachstate ( &thrAttr, PTHREAD_CREATE_JOINABLE );
   
   /* Vytvareni vlaken
    */  
   for ( i = 0; i < thr; i ++ )
    if ( pthread_create ( &arg[i] . m_ThrID, &thrAttr, thrFunc, &arg[i] ) )
     {
       free ( arg );
       perror ( "Create thread\n" );
       pthread_mutex_destroy( &g_Mtx );
       pthread_attr_destroy ( &thrAttr );
       return ( 1 );
     }
   pthread_attr_destroy ( &thrAttr );
 
   /* Cekani na dokonceni
    */
   for ( i = 0; i < thr; i ++ )
    pthread_join ( arg[i].m_ThrID, &dummy );

    printf("%d", g_Sum);

   /* Uklid
    */
   pthread_mutex_destroy( &g_Mtx );
   free ( arg );
   return ( 0 ); 
 }
