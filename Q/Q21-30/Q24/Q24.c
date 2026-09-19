#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    // TODO: Call fork().
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        return 1;
    }

    // TODO: In the parent process:
    //       - Print the parent PID using getpid().
    //       - Terminate immediately using _exit(0).
    if (pid != 0) {
        printf("Parent PID: %d\n", getpid());
        _exit(0);
    }
    // TODO: In the child process:
    //       - Print the original parent PID using getppid().
    //       - Sleep using sleep(5) to guarantee parent terminates first.
    //       - Retrieve and print the new parent PID using getppid() to verify adoption.
    if (pid == 0) {
        printf("Parent PID: %d\n", getppid());
        sleep(5);
        printf("Parent PID: %d\n", getppid());
    }
    return 0;
}