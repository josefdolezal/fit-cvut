#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
  printf ("\n\nThe process id is %d\n", (int) getpid ());
  printf ("The parent process id is %d\n", (int) getppid ());

  sleep(30);
  return EXIT_SUCCESS;
}
