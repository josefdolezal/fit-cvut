/* Program paralene vypocte umocneni matice A^n. Velikost matice A a mocnina n jsou
 * parametry na prikazove radce. Matice A je vygenerovana, bude obsahovat nahodna cisla.
 *
 * Paralelni reseni pocita vysledek podle predpisu:
 *      vysledek = A*(A*(A* .... *(A * A))))
 * Vlakna vypocet urychli tim, ze kazde vlakno dostane za ukol vypocet jedne radky vysledku
 * (vlaken bude vytvoreno tolik, kolik je radek v matici).
 *
 * Vzdy po dokonceni vypoctu radku nasobeni na sebe vlakna pockaji na bariere. Tim maji jistotu,
 * ze matice je konzistentni a muze byt nasobena dale.
 *
 * Reseni neni nejlepsi mozne. Lepsi by bylo provadet postupne umocnovani matice na druhou a
 * do vysledku pridavat pouze vybrane mocniny podle binarniho tvaru exponentu (slozitost by se
 * snizila z O(power * size ^3) na O(log(power) * n^3).
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <assert.h>



typedef struct TMatrix
 {
   int    m_Size;        /* velikost ctvercove matice */
   int ** m_Data;        /* data matice */
 } TMATRIX;

typedef struct TThr      /* struktura dat predavanych vlaknum */
 {
   int        m_Power;   /* mocnina zadana z prikazove radky */
   int        m_Idx;     /* radka vysledku, ktera bude pocitana timto vlaknem */
   pthread_t  m_ThrID;   /* identiofikator vlakna */
 } TTHR;


TMATRIX  * g_A;          /* matice nahodnych hodnot */
TMATRIX  * g_M1;         /* matice pro mezivysledek */
TMATRIX  * g_M2;         /* matice pro mezivysledek */
pthread_barrier_t g_Barrier; /* bariera */


/*---------------------------------------------------------------------------*/
/* Alokace ctvercove matice zadane velikosti
 */
TMATRIX * allocMatrix ( int size )
 {
   TMATRIX * m;
   int i;
   
   m = (TMATRIX *) malloc ( sizeof ( *m ) );
   m -> m_Size = size;
   m -> m_Data = (int **) malloc ( sizeof ( *m -> m_Data ) * size );
   for ( i = 0; i < size; i ++ )
    m -> m_Data[i] = (int *) malloc ( sizeof (*m -> m_Data[i]) * size );
   return ( m );
 }
/*---------------------------------------------------------------------------*/
/* Alokace ctvercove matice zadane velikosti, vyplnene nahodnym obsahem
 */
TMATRIX * randomMatrix ( int size )
 {
   TMATRIX  * m = allocMatrix ( size );
   int i, j;

   for ( i = 0; i < size; i ++ )
    for ( j = 0; j < size; j ++ )
     m -> m_Data[i][j] = rand () % 100;
   return ( m );
 }
/*---------------------------------------------------------------------------*/
/* Alokace ctvercove matice zadane velikosti, nastavena jako jednotkova matice
 */
TMATRIX * unitMatrix ( int size )
 {
   TMATRIX  * m = allocMatrix ( size );
   int i, j;

   for ( i = 0; i < size; i ++ )
    for ( j = 0; j < size; j ++ )
     m -> m_Data[i][j] = i == j; /* 1 na hlavni diagonale */
   return ( m );
 }
/*---------------------------------------------------------------------------*/
/* Zobrazeni matice
 */
void printMatrix ( TMATRIX * m )
 {
   int i, j;
   
   for ( i = 0; i < m -> m_Size; i ++ )
    {
      for ( j = 0; j < m -> m_Size; j ++ )
       printf ( "%d ", m -> m_Data[i][j] );
      printf ( "\n" );
    }
 }
/*---------------------------------------------------------------------------*/
/* Uvolneni pameti pro matici
 */
void freeMatrix ( TMATRIX * m )
 {
   int i;
   
   for ( i = 0; i < m -> m_Size; i ++ )
    free ( m -> m_Data[i] );
   free ( m -> m_Data );
   free ( m );
 }
/*---------------------------------------------------------------------------*/
/* Nasobeni matice - c = a * b. Predpoklada, ze vsechny matice jsou alokovane
 * a maji stejnou velikost. Prepise obsah matice c.
 */
void mulMatrix ( TMATRIX * a, TMATRIX * b, TMATRIX * c )
 {
   int size, sum, i, j, k;
   
   assert ( a -> m_Size == b -> m_Size && b -> m_Size == c -> m_Size );
   size = a -> m_Size;
   
   for ( i = 0; i < size; i ++ )
    for ( j = 0; j < size; j ++ )
     {
       sum = 0;
       for ( k = 0; k < size; k ++ )
        sum += a -> m_Data[i][k] * b -> m_Data[k][j];
       c -> m_Data[i][j] = sum;
     }
 }
/*---------------------------------------------------------------------------*/
/* Vlakno provadejici nasobeni.
 */
void * thrFunc ( TTHR * p )
 {
   int power = p -> m_Power, idx = p -> m_Idx, size = g_A -> m_Size;
   int i, j, sum, res;

   /* Pocet iteraci (mocneni)
    */
   while ( power -- )
    {
      /* Pocitame radku idx vysledku, nasobime A * M1. Na pocatku je M1 nastavene na
       * jednotkovou matici. Vysledek ukladame do M2 na odpovidajici pozici.
       */
      for ( i = 0; i < size; i ++ )
       {
         sum = 0;
         for ( j = 0; j < size; j ++ )
          sum += g_A -> m_Data[idx][j] * g_M1 -> m_Data[j][i];
         g_M2 -> m_Data[idx][i] = sum;
       }
       
      /* Pockame na ostatni vlakna dokud nedopocitaji sve radky.
       */
      res = pthread_barrier_wait ( &g_Barrier );
      /* M1 obsahovalo puvodni matici, M2 jsme vypocetli jako A * M1.
       * Pro dalsi iteraci mocneni udelame z M2 zdroj a z M1 cil.
       * Potrebujeme prohodit odkazy na matice M1 a M2.
       */

      if ( res == PTHREAD_BARRIER_SERIAL_THREAD )
       {
         /* Jedno z vlaken dostane jako navratovou hodnotu
          * PTHREAD_BARRIER_SERIAL_THREAD. Ostatni dostanou nulu.
          * Bariera nam takto vybere "jedno" vlakno, toho vyuzijeme zde.
          * Potrebujeme prohodit odkazy M1 a M2 -> prohozeni provede
          * to vybrane vlakno.
          */
         TMATRIX * tmp = g_M1;
         g_M1 = g_M2;
         g_M2 = tmp;
       }
       
      pthread_barrier_wait ( &g_Barrier );
      /* Cekame znovu na vsechan vlakna, zde mame jistotu, ze M1 a M2 jsou
P       * spravne prohozene (=pripravene) pro dalsi iteraci.
       */
    }
   return ( NULL );
 }
/*---------------------------------------------------------------------------*/
/* Paralelni reseni s vlakny.
 */
void threadedPower ( int power, int size )
 {
   TTHR           * param;
   pthread_attr_t   attr;
   int              i;

   /* Pole parametru vlaken. Vytvorime _size_ vlaken, pro kazdou radku matice jedno.
    * Kazde vlakno bud emit na starosti vypocet jedne radky vysledku.
    */
   param = (TTHR *) malloc ( sizeof ( *param ) * size );
   for ( i = 0; i < size; i ++ )
    {
      param[i] . m_Idx = i;
      param[i] . m_Power = power;
    }

   pthread_attr_init ( &attr );
   pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE );

   pthread_barrier_init ( &g_Barrier, NULL, size );


   for ( i = 0; i < size; i ++ )
    if ( pthread_create ( &param[i] . m_ThrID, &attr, (void*(*)(void*)) thrFunc, (void*)&param[i] ) )
     {
       perror ( "pthread_create" );
       return;
     }
   pthread_attr_destroy ( &attr );  
     
   for ( i = 0; i < size; i ++ )
    pthread_join ( param[i] . m_ThrID, NULL );

   free ( param );
   pthread_barrier_destroy ( &g_Barrier );
 }
/*---------------------------------------------------------------------------*/
/* Sekvencni resni
 */
void sequentialPower ( int power, int size )
 {
   int i;
   TMATRIX * tmp;

   for ( i = 0; i < power; i ++ )
    {
      mulMatrix ( g_A, g_M1, g_M2 );
      tmp = g_M1;
      g_M1 = g_M2;
      g_M2 = tmp;
    }
 }
/*---------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
 {
   int              size, power, useThreads;
   
   
   if ( argc != 4 || sscanf ( argv[1], "%d", &size ) != 1
                  || sscanf ( argv[2], "%d", &power ) != 1
                  || sscanf ( argv[3], "%d", &useThreads ) != 1
                  || size < 1 || power < 0 )
    {
      printf ( "Usage: %s <size> <power> <use_threads>\n", argv[0] );
      return ( 1 );
    }

   g_A   = randomMatrix ( size );
   g_M1  = unitMatrix   ( size );
   g_M2  = allocMatrix  ( size );

   if ( useThreads )
     threadedPower   ( power, size );
    else
     sequentialPower ( power, size );

/*
   printf ( "Puvodni matice:\n") ;
   printMatrix ( g_A );

   printf ( "Umocnena na %d:\n", power );
   printMatrix ( g_M1 );
*/
   freeMatrix ( g_M2 );
   freeMatrix ( g_M1 );
   freeMatrix ( g_A );
   return ( 0 );
 }
