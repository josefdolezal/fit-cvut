/* ----------------------------------------------------------------- */
/* PROGRAM  pingpong:                                                */
/*    This program forces two threads to execute alternately.        */
/* ----------------------------------------------------------------- */

#include  <stdio.h>
#include  <stdlib.h>
#include  <pthread.h>
#include  <semaphore.h>

sem_t    Wait_for_A, Wait_for_B;        /* blocking semaphores      */

int       Max_Run;

/* ----------------------------------------------------------------- */
/* FUNCTION  ThreadA()                                               */
/* ----------------------------------------------------------------- */

void *thread_A( void * arg )
{
  int i;
  pthread_t tid;

  tid = pthread_self();  
  printf("thread_A(): %d is started.\n", (int) tid);
  for (i = 1; i <= Max_Run; i++) {
    sem_wait(&Wait_for_A);
    printf("thread_A(): %d is running.\n", (int) tid);
    sem_post(&Wait_for_B);
  }
  printf("thread_A(): %d exit.\n", (int) tid);
  pthread_exit(NULL);
}

/* ----------------------------------------------------------------- */
/* FUNCTION  ThreadB()                                               */
/* ----------------------------------------------------------------- */

void *thread_B( void * arg )
{
  int i;
  pthread_t tid;
    
  tid = pthread_self(); 
  printf("thread_B(): %d is started.\n", (int) tid);
  for (i = 1; i <= Max_Run; i++)  {
    sem_wait(&Wait_for_B);
    printf("thread_B(): %d is running.\n", (int) tid);
    sem_post(&Wait_for_A);
  }
  printf("thread_B(): %d exit.\n", (int) tid);
  pthread_exit(NULL);
}

/* ----------------------------------------------------------------- */
/*                        The main program                           */
/* ----------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  pthread_t tid, tid_A, tid_B;
  pthread_attr_t attr; 
  int rc;

  if (argc != 2) {
    printf("Usage: %s   number_of_iterations\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  Max_Run = abs(atoi(argv[1]));

  tid = pthread_self();
  printf("main(): %d started ...\n", (int) tid);

  /* ------------------------------------------------------------ */
  /* Wait_for_A   1: we want A gets through first than notifies B */
  /* Wait_for_B   0: B should be blocked until notified by A      */
  /* ------------------------------------------------------------ */

  sem_init(&Wait_for_A, 0, 1);
  sem_init(&Wait_for_B, 0, 0);
     

  /*  For portability, explicitly create threads in a joinable state */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  rc = pthread_create(&tid_A, NULL, thread_A, NULL);
  if (rc != 0) {
    fprintf(stderr,"ERROR: return code from pthread_create() is %d\n", rc);
    exit(EXIT_FAILURE);
  };
  rc = pthread_create(&tid_B, NULL, thread_B, NULL);
  if (rc != 0) {
    fprintf(stderr,"ERROR: return code from pthread_create() is %d\n", rc);
    exit(EXIT_FAILURE);
  };

  pthread_join(tid_A, NULL);
  pthread_join(tid_B, NULL);

  sem_destroy(&Wait_for_A);
  sem_destroy(&Wait_for_B);

  printf("main(): %d exits.\n", (int) tid);

  return (EXIT_SUCCESS);
}
