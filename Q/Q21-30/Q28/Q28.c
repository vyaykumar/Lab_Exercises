#include <unistd.h>
#include <sched.h>
#include <stdio.h>

int main(void) {
    // TODO: Get current scheduling policy using sched_getscheduler(0).
    int current_policy = sched_getscheduler(0);
    if (current_policy == -1) {
        perror("sched_getscheduler() failed");
        return 1;
    }

    // TODO: Declare and set struct sched_param.
    //       - param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    struct sched_param sp;
    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (sp.sched_priority == -1) {
        perror("sched_get_priority_max() failed");
        return 1;
    }

    // TODO: Change policy to SCHED_FIFO or SCHED_RR using:
    //       sched_setscheduler(0, SCHED_FIFO, &param).
    if (sched_setscheduler(0, SCHED_FIFO, &sp) == -1) {
        perror("sched_setscheduler failed (run with sudo)");
        return 1;
    }

    // TODO: Verify the updated policy using sched_getscheduler(0).
    int new_policy = sched_getscheduler(0);
    if (new_policy == SCHED_FIFO)
        write(STDOUT_FILENO, "Successfully changed to SCHED_FIFO\n", 35);
     else
        write(STDERR_FILENO, "Policy mismatch\n", 16);

    return 0;
}
