#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h>

int              g_Cnt = 0;
pthread_mutex_t  g_Mtx;
pthread_cond_t   g_Cond1, g_Cond2;

void * thr1 ( void * arg )
 {
   int val;

   while ( 1 )
    {
      pthread_mutex_lock ( &g_Mtx );
      if ( g_Cnt < 10000 ) g_Cnt ++;
      val = g_Cnt;
      pthread_mutex_unlock ( &g_Mtx );
      if ( val >= 10000 ) break;
    }

   pthread_mutex_lock ( &g_Mtx );
   pthread_cond_broadcast ( &g_Cond2 );
   while(g_Cnt<50000)
    pthread_cond_wait ( &g_Cond1, &g_Mtx );
   pthread_mutex_unlock ( &g_Mtx );
   printf ( "Counter = %d\n", g_Cnt );
   return ( NULL );
 }

void * thr2 ( void * arg )
 {
   int val;

/*   usleep ( 100000 ); */
   pthread_mutex_lock ( &g_Mtx );
   while(g_Cnt < 10000)
    pthread_cond_wait ( &g_Cond2, &g_Mtx );
   pthread_mutex_unlock ( &g_Mtx );
   while ( 1 )
    {
      pthread_mutex_lock ( &g_Mtx );
      if ( g_Cnt < 50000 ) g_Cnt ++;
      val = g_Cnt;
      pthread_mutex_unlock ( &g_Mtx );
      if ( val == 50000 ) break;
    }
   pthread_mutex_lock ( &g_Mtx );
   pthread_cond_broadcast ( &g_Cond1 );
   pthread_mutex_unlock ( &g_Mtx );
   printf ( "Counter = %d\n", g_Cnt );
   return ( NULL );
 }

int main ( int argc, char * argv [] )
 {
   int              i;
   pthread_t        thrID[4];
   pthread_attr_t   attr;

   pthread_attr_init ( &attr );
   pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE );

   pthread_mutex_init ( &g_Mtx, NULL );
   pthread_cond_init ( &g_Cond1, NULL );
   pthread_cond_init ( &g_Cond2, NULL );

   for ( i = 0; i < 4; i ++ )
    if ( pthread_create ( &thrID[i], &attr, i < 2 ? thr1 : thr2, NULL ) )
     {
       perror ( "pthread_create" );
       return ( 1 );    
     }
   pthread_attr_destroy ( &attr );  

   for ( i = 0; i < 4; i ++ )
    pthread_join ( thrID[i], NULL );  

   pthread_cond_destroy ( &g_Cond1 );
   pthread_cond_destroy ( &g_Cond2 );
   pthread_mutex_destroy ( &g_Mtx );
   return ( 0 );
 }

