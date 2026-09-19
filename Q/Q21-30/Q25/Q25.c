#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // TODO: Create child 1 using fork().
    // TODO: Create child 2 using fork().
    // TODO: Create child 3 using fork().

    // TODO: In each child:
    //       - Sleep for different intervals (e.g., child 1 sleeps 2s, child 2 sleeps 5s).
    //       - Exit using _exit(0).

    // TODO: In the parent process:
    //       - Call waitpid(target_pid, &status, 0) targeting child 2 specifically.
    //       - Inspect status using WIFEXITED(status) and WEXITSTATUS(status).

    return 0;
}