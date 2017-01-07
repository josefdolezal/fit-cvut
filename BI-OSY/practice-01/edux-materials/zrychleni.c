/* Zrychleni vypoctu paralelizaci ulohy s vyuzitim POSIXovych vlaken. 
   20.3.-2.4.2007 Jan Zdarek - X36OSY - KP FEL CVUT, zdarekj@fel 
Pro maximalni zkraceni kodu bylo obetovano mnoho kodu, ktery dela program 
skutecne pouzitelnym, napr.: parametrizace ulohy z prikazove radky, 
testovani navratovych kodu vsech funkci, ktere neco vraci - v kodu nize chybi 
mj. testovani kodu funkci pthread_attr_*(3).
Obcas take neuskodi resit problemy jinak, nez pomoci exit(3), atd. */
/* *** Preklad ***
   gcc -Wall -pedantic -ansi -lpthread -o zrychleni zrychleni.c
*/
#include <pthread.h>
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* malloc() a spol., EXIT_* */
#include <sys/times.h> /* struct tms, times() */

#ifndef TYP_POLE
  #define TYP_POLE unsigned long int
#endif

#ifndef TYP_VYSLEDKU
  #define TYP_VYSLEDKU TYP_POLE
#endif

struct args {
  TYP_POLE* pole;
  unsigned int delka;
};

void *pocitej(void *arg) {
  unsigned int i;
  struct args* param=(struct args*)arg;
  TYP_VYSLEDKU* vysledek=NULL;
  
  if((vysledek=(TYP_VYSLEDKU*)calloc(1,sizeof(TYP_VYSLEDKU)))==NULL) 
    exit(EXIT_FAILURE);
  for(i=0; i<param->delka; i++) {
    (*vysledek)+=(param->pole[i]);
  }
  return vysledek;
}

int main(int argc, char* argv[]) {
  pthread_attr_t attr;
  int i;
  struct tms tms_start,tms_stop,tms_stop2;
  clock_t clk_start,clk_stop;
  TYP_VYSLEDKU soucet=(TYP_VYSLEDKU)0;
  struct args* pole_args=NULL;
  pthread_t* threads=NULL;
  TYP_POLE* pole=NULL;
  unsigned int pocet_vlaken=4;
  unsigned int delka_pole=5000000;
  unsigned int delka_useku=delka_pole/pocet_vlaken;
  unsigned int delka_1_useku=delka_useku+delka_pole-(delka_useku*pocet_vlaken);

  if((pole_args=(struct args*)malloc(pocet_vlaken*sizeof(struct args)))==NULL)
    exit(EXIT_FAILURE);
  if((threads=(pthread_t*)malloc(pocet_vlaken*sizeof(pthread_t)))==NULL)
    exit(EXIT_FAILURE);
  if((pole=(TYP_POLE*)malloc(delka_pole*sizeof(TYP_POLE)))==NULL)
    exit(EXIT_FAILURE);

  for(i=0;i<delka_pole;i++) {
    pole[i]=i%pocet_vlaken;
  }

  puts("/* Sekvencni reseni */");
  if((clk_start=times(&tms_start))==-1) exit(EXIT_FAILURE);
  for(i=0;i<delka_pole;i++) { soucet+=pole[i]; }
  if((clk_stop=times(&tms_stop))==-1) exit(EXIT_FAILURE);
  printf("Soucet je: %lu\n",(unsigned long int)soucet);

  printf("Cas celkovy: %lu ticks.\nUser space: %lu ticks.\nSystem: %lu ticks.\n",
    (unsigned long int)clk_stop-clk_start,
    (unsigned long int)(tms_stop.tms_utime-tms_start.tms_utime),
    (unsigned long int)(tms_stop.tms_stime-tms_start.tms_stime));
 
  puts("/* Paralelni reseni */");
  soucet=(TYP_VYSLEDKU)0;
  if((clk_start=times(&tms_start))==-1) exit(EXIT_FAILURE);

  if(delka_useku!=delka_1_useku) {
    fprintf(stderr,"Pole nejde delit beze zbytku: |pole|=%u, |usek|=%u, |1. usek|=%u.\n",delka_pole,delka_useku,delka_1_useku);
  }
  
  /* Vlakna explicitne vytvorime jako joinable, nespolehame se, ze to nekdo 
     udela za nas. */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  for (i=0; i < pocet_vlaken; i++) {
    static unsigned int offset=0;

    pole_args[i].pole=pole+offset;
    if(i!=0) {
      pole_args[i].delka=delka_useku;
      offset+=delka_useku;
    } else {
      pole_args[i].delka=delka_1_useku;
      offset+=delka_1_useku;
    }
    if(pthread_create(&threads[i], &attr, pocitej, (void *)&pole_args[i])!=0) {
      fprintf(stderr,"Vlakno c. %d se nespustilo.\n",i);
    }
  }
  /* Atributy vlaken uz nebudeme dale potrebovat - uvolnime prostredky knihovny. */
  pthread_attr_destroy(&attr);

  /* Join + nacteni vysledku z vlaken. */
  for (i = 0; i < pocet_vlaken; i++) {
    TYP_VYSLEDKU* vysledek;
    int r=pthread_join(threads[i], (void**)&vysledek);
    if(r!=0 || vysledek==NULL || vysledek==PTHREAD_CANCELED) {
      fprintf(stderr,"main(): problem vlakna c. %d s vracenim vysledku.\n",i);
    } else {
      soucet+=*vysledek;
      /* Nesmime zapomenout na dealokaci, ale reinicializace na NULL zde neni 
         potreba - lokalni promenna. */
      free(vysledek); 
    }
  }
  if((clk_stop=times(&tms_stop2))==-1) exit(EXIT_FAILURE);
  fprintf(stderr,"main() - ukonceno vlaken: %u.\n", pocet_vlaken); 
  printf("Soucet je: %lu\n",(unsigned long int)soucet);


  printf("Cas celkovy: %lu ticks.\nUser space: %lu ticks.\nSystem: %lu ticks.\n",
    (unsigned long int)(clk_stop-clk_start),
    (unsigned long int)(tms_stop2.tms_utime-tms_stop.tms_utime),
    (unsigned long int)(tms_stop2.tms_stime-tms_stop.tms_stime));
  
  /* Uklid pameti overi, zda jsme s ukazateli pracovali korektne. */
  pthread_attr_destroy(&attr);
  free(pole); pole=NULL;
  free(threads); threads=NULL;
  free(pole_args); pole_args=NULL;

  return EXIT_SUCCESS;
}
