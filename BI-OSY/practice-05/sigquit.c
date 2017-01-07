#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

sig_atomic_t sig_count = 0;

void handler (int signal_number)
{
  ++sig_count;
}

int main ()
{ 
  int c=0;
  struct sigaction sa; 

  memset (&sa, 0, sizeof (sa));
  sa.sa_handler = &handler;
  sigaction (SIGQUIT, &sa, NULL);
  
  printf("\nPress 'CTRL C' to quit or 'CTRL \\'  to send signal SIGQUIT\n\n");
  while (1) { 
    if ( c<sig_count ) { 
    printf ("SIGQUIT was raised %d times\n", sig_count);
    c=sig_count;
    }
  }
  return EXIT_SUCCESS;
}
