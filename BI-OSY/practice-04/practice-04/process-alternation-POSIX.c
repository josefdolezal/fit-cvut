/* ----------------------------------------------------------------- */
/* PROGRAM  pingpong:                                                */
/*    This program forces two processes to execute alternately.        */
/* ----------------------------------------------------------------- */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

struct shared {
  sem_t mutexA, mutexB;
} shared, *ptr;

int Max_Run;

void parent_code (pid_t pid)
{
  int   i;

  printf("Parent %d: I started.\n", (int) pid);
  for (i = 1; i <= Max_Run; i++) {
    sem_wait(&ptr->mutexA);
    printf("Parent %d: I am running.\n", (int) pid);
    sem_post(&ptr->mutexB);
  }
}

void child_code (pid_t pid)
{
  int   i;

  printf("Child  %d: I started.\n", (int) pid);
  for (i = 1; i <= Max_Run; i++) {
    sem_wait(&ptr->mutexB);
    printf("Child  %d: I am running.\n", (int) pid);
    sem_post(&ptr->mutexA);
  }
}

int  main(int argc,  char *argv[])
{
  pid_t id, pid;
  int status;

  if (argc != 2) {
    printf("Use %s #-of-iterations\n", argv[0]);
    exit(0);
  }
  Max_Run = abs(atoi(argv[1]));

  /* shared memory via mmap if MAP_ANONYMOUS is not supported
   * 
   * zfd = open("/dev/zero", O_RDWR);
   * ptr = (struct shared *) mmap( NULL, 
   *                             sizeof(struct shared), 
   *                             PROT_READ | PROT_WRITE, MAP_SHARED, 
   *                             zfd, 
   *                             0);
   */                              
  ptr = (struct shared *) mmap( NULL, 
                                sizeof(struct shared), 
                                PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,  
                                -1, 
                                0);
  
  if (sem_init(&ptr->mutexA, 1, 1) != 0)
    { perror ("error in the function sem_init()");
      exit(1);
    };
  if (sem_init(&ptr->mutexB, 1, 0) != 0)
    { perror ("error in the function sem_init()");
      exit(1);
    };
     
  id = fork ();
  switch (id) {
  case -1: /* fork error */
    perror ("error in the function fork()");
    exit(1);
  case 0:  /* child code */ 
    pid=getpid();
    child_code(pid);
    printf ("Child  %d: I exit.\n", (int) pid);
    exit (0); 
  default: /* parent code */ 
    pid=getpid();
    parent_code(pid);
    wait(&status);
  };

  sem_destroy(&ptr->mutexA);
  sem_destroy(&ptr->mutexB);

  printf ("Parent %d: I exit.\n", (int) pid);
  return (EXIT_SUCCESS);
}

