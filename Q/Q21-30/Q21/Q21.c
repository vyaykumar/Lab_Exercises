#include <unistd.h>
#include <sys/types.h>

int main(void) {
    // TODO: Invoke the fork() system call.

    // TODO: Verify fork() return value for error handling (-1).

    // TODO: In the child branch (return value == 0):
    //       - Retrieve child PID using getpid().
    //       - Retrieve parent PID using getppid().
    //       - Write details to STDOUT_FILENO using write().

    // TODO: In the parent branch (return value > 0):
    //       - Retrieve parent PID using getpid().
    //       - Retrieve child PID from fork return value.
    //       - Write details to STDOUT_FILENO using write().

    return 0;
}