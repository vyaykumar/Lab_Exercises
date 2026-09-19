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

    // TODO: In the child process:
    //       - Terminate immediately using _exit(0).
    if (pid == 0) {
        _exit(0);
    }

    // TODO: In the parent process:
    //       - Sleep using sleep(30) or pause() to keep the parent alive.
    //       - Do not call wait() or waitpid().
    if (pid != 0) {
        printf("Parent PID: %d\n", getpid());
        printf("Child (zombie) PID: %d\n", pid);
        printf("Sleeping for 30 seconds. Check process table with 'ps -l' or 'ps aux'...\n");

        sleep(30);
    }

    return 0;
}