#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    // TODO: Invoke the fork() system call.
    pid_t child = fork();

    // TODO: Verify fork() return value for error handling (-1).
    if (child == -1) {
        perror("fork() failed");
        return 1;
    }

    // TODO: In the child branch (return value == 0):
    //       - Retrieve child PID using getpid().
    //       - Retrieve parent PID using getppid().
    //       - Write details to STDOUT_FILENO using write().

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

    // TODO: In the parent branch (return value > 0):
    //       - Retrieve parent PID using getpid().
    //       - Retrieve child PID from fork return value.
    //       - Write details to STDOUT_FILENO using write().
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