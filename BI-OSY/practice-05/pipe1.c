#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 100

int main(void)
{
  int     n, fds[2];
  pid_t   pid;
  char    line[MAXLINE];

  /* Create a pipe.  File descriptors for the two ends of the pipe are placed in fds.  */
  pipe(fds);
   
  /* Fork a child process.  */
  pid = fork();

  if (pid > 0) {        /* parent */
    close(fds[0]);
    write(fds[1], "hello world\n", 12); }
  else {                /* child */
    close(fds[1]);
    n = read(fds[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);
  }

  return EXIT_SUCCESS;
}


