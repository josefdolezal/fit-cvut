/* producent-konzument reseny pomoci semaforu. Program obsahuje
 * celkem 4 velmi zavazne chyby. Najdete je.
 *
 * Producenti (kazdy) produkuji cisla od 0 do nekonecna (MAX_INT)
 * Konzumenti zobrazuji ziskane hodnoty a informaci o tom, od koho je.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int g_Pos = 0;
struct
 {
   int m_ID;
   int m_Val;
 } g_Buffer[BUFFER_SIZE];

pthread_mutex_t  g_Mtx;
sem_t g_Full, g_Free;

void * prodFunc ( intptr_t  id )
 {
   int i, j, a = 0;
   
   for ( i = 0; ; i ++ )
    {
      for ( j = 0; j < 5000; j ++ ) /* it takes some time to "produce" */
       a += j;
      sem_wait ( &g_Free );
      pthread_mutex_lock ( &g_Mtx );
      g_Buffer[g_Pos] . m_ID  = id;
      g_Buffer[g_Pos] . m_Val = i;
      g_Pos ++;
      pthread_mutex_unlock ( &g_Mtx );
      sem_post ( &g_Full );

      printf ( "Producer %d done\n", (int)id );
    }
   return ( NULL );
 }

void * consFunc ( intptr_t  id )
 {
   int from, val;
   while ( 1 )
    {
      sem_wait ( &g_Full );
      pthread_mutex_lock ( &g_Mtx );
      g_Pos --;
      from = g_Buffer[g_Pos] . m_ID;
      val = g_Buffer[g_Pos] . m_Val;
      pthread_mutex_unlock ( &g_Mtx );
      sem_post ( &g_Free );
      printf ( "Consumer %d received %d from %d\n", (int)id, val, from );
    }
   return ( NULL );
 }

int main ( int argc, char * argv [] )
 {
   int              prod, cons, i;
   pthread_t      * thrID;
   pthread_attr_t   attr;
   
   
   if ( argc != 3 || sscanf ( argv[1], "%d", &prod ) != 1
                  || sscanf ( argv[2], "%d", &cons ) != 1
                  || prod < 1 || cons < 1 )
    {
      printf ( "Usage: %s <prod> <cons>\n", argv[0] );
      return ( 1 );
    }
    
   thrID = (pthread_t *) malloc ( sizeof ( *thrID ) * ( prod + cons ) );
   pthread_attr_init ( &attr );
   pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE );

   pthread_mutex_init ( &g_Mtx, NULL );
   sem_init ( &g_Free, 0, BUFFER_SIZE );
   sem_init ( &g_Full, 0, 0 );
     
     
     

   for ( i = 0; i < cons; i ++ )
    if ( pthread_create ( &thrID[i], &attr, (void*(*)(void*)) consFunc, (void*)(intptr_t) (i + 1) ) )
     {
       perror ( "pthread_create" );
       return ( 1 );    
     }
   for ( i = 0; i < prod; i ++ )
    if ( pthread_create ( &thrID[i + cons], &attr, (void*(*)(void*)) prodFunc, (void*)(intptr_t) (i + 1) ) )
     {
       perror ( "pthread_create" );
       return ( 1 );    
     }
   pthread_attr_destroy ( &attr );  
     
   for ( i = 0; i < prod + cons; i ++ )
    pthread_join ( thrID[i], NULL );  6

   pthread_mutex_destroy ( &g_Mtx );
   sem_destroy ( &g_Free );
   sem_destroy ( &g_Full );

   free ( thrID );
   return ( 0 );
 } 

