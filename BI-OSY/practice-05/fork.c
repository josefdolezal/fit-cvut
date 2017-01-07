#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    printf("the main program process id is %d\n", (int) getpid());

    child_pid = fork();
    switch (child_pid) {
        case -1:  /* Error */
            fprintf(stderr, "Error: fork()");
            exit(EXIT_FAILURE);
        case 0:   /* Children code */
            printf("this is the child process, with id %d\n", (int) getpid());
            sleep(60);
            break;
        default:  /* Parent code */
            printf("this is the parent process, with id %d\n", (int) getpid());
            printf("the child's process id is %d\n", (int) child_pid);
            sleep(30);
    };
    return EXIT_SUCCESS;
}
