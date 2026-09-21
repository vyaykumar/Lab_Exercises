#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        return 1;
    }

    if (pid != 0) {
        printf("[Parent] PID: %d\n", getpid());
        fflush(stdout);
        _exit(0);
    }

    if (pid == 0) {
        printf("[Child] Parent PID: %d\n", getppid()); fflush(stdout);
        sleep(5);
        printf("[Child] Parent PID: %d\n", getppid()); fflush(stdout);
    }
    return 0;
}