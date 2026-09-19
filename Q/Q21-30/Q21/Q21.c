#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t child = fork();

    if (child == -1) {
        perror("fork() failed");
        return 1;
    }

    if (child == 0) {
        pid_t pid = getpid();
        pid_t ppid = getppid();

        char buffer[128];
        int len = snprintf(buffer, sizeof(buffer), "Child Process\nPID: %d\nPPID: %d\n", pid, ppid);
        if (len > 0 && (write(STDOUT_FILENO, buffer, len) < 0)) {
            perror("child write() failed");
            return 1;
        }
    }

    else {
        pid_t pid = getpid();
        pid_t cid = child;

        char buffer[128];
        int len = snprintf(buffer, sizeof(buffer), "Parent Process\nPID: %d\nChild PID: %d\n", pid, cid);
        if (len > 0 && write(STDOUT_FILENO, buffer, len) < 0) {
            perror("parent write() failed");
            return 1;
        }
    }

    return 0;
}