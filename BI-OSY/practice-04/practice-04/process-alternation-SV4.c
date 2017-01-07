/* ----------------------------------------------------------------- */
/* PROGRAM  pingpong:                                                */
/*    This program forces two processes to execute alternately.        */
/* ----------------------------------------------------------------- */
 
#include <stdio.h>
#include <stdlib.h>
/* #include <sys/types.h> */
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>

#define NUMSEM 2

int Max_Run;

/*
union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;  
};
*/

union semun {
  int val;
  struct semid_ds *buf;
  ushort *array;
};

int semaphore_allocation (key_t key)
{     
  int rc;

  if ( (rc=semget (key, NUMSEM, IPC_CREAT | 0700)) == -1 )
    {
      perror ("error in the function semaphore_allocation()");
      exit (1);
    };   
  return rc; 
}

int semaphore_initialize (int semid, int valA, int valB)
{
  int rc;
  union semun argument;
  unsigned short values[NUMSEM];
  values[0] = valA;
  values[1] = valB;
  argument.array = values;
  if ((rc=semctl (semid, NUMSEM, SETALL, argument)) == -1)
    {
      perror ("error in the function semaphore_initialize()");
      exit (1);
    };
  return rc; 
}

int semaphore_destroy (int semid)
{     
  union semun;
  int rc;
  if ( (rc=semctl(semid, NUMSEM, IPC_RMID, NUMSEM)) == -1)
    {
      perror ("error in the function semaphore_destroy()");
      exit (1);
    };
  return rc;
}

int semaphore_down (int semid, int semnum)
{
  struct sembuf operations[1];
  operations[0].sem_num = semnum;   /* Use the first counter. */
  operations[0].sem_op = -1;        /* Decrement by 1.  */
  operations[0].sem_flg = SEM_UNDO; /* Permit undo'ing.  */

  return semop (semid, operations, 1);
}
int semaphore_up (int semid, int semnum)
{
  struct sembuf operations[1];
  operations[0].sem_num = semnum;   /* Use the first counter  */
  operations[0].sem_op = 1;         /* Increment by 1.  */
  operations[0].sem_flg = SEM_UNDO; /* Permit undo'ing.  */

  return semop (semid, operations, 1);
}

void parent_code (pid_t pid, int semid)
{
  int   i;

  printf("Parent %d: I started.\n", (int) pid);
  for (i = 1; i <= Max_Run; i++) {
    semaphore_down(semid, 0);
    printf("Parent %d: I am running.\n", (int) pid);
    semaphore_up(semid, 1);
  }
}

void child_code (pid_t pid, int semid)
{
  int   i;

  printf("Child  %d: I started.\n", (int) pid);
  for (i = 1; i <= Max_Run; i++) {
    semaphore_down(semid, 1);
    printf("Child  %d: I am running.\n", (int) pid);
    semaphore_up(semid, 0);
  }
}

int  main(int argc,  char *argv[])
{
  pid_t id, pid;
  int status, semid;
  key_t semkey = IPC_PRIVATE;       /* key to pass to semget() */

  if (argc != 2) {
    printf("Use %s #-of-iterations\n", argv[0]);
    exit(0);
  }
  Max_Run = abs(atoi(argv[1]));
     
  semid=semaphore_allocation(semkey);
  semaphore_initialize(semid,1,0);

  id = fork ();
  switch (id) {
  case -1: /* fork error */
    perror ("error in the function fork()");
    exit(1);
  case 0:  /* child code */ 
    pid=getpid();
    child_code( pid, semid);
    printf ("Child  %d: I exit.\n", (int) pid);
    exit (0); 
  default: /* parent code */ 
    pid=getpid();
    parent_code( pid, semid);
    wait(&status);
  };

  semaphore_destroy(semid);
    
  printf ("Parent %d: I exit.\n", (int) pid);
  return EXIT_SUCCESS;
}

