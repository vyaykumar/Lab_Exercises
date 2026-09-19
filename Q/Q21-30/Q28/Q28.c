#include <unistd.h>
#include <sched.h>

int main(void) {
    // TODO: Get current scheduling policy using sched_getscheduler(0).
    int sched_res = sched_getscheduler(0);
    // TODO: Declare and set struct sched_param.
    //       - param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    struct sched_param sp;
    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);

    // TODO: Change policy to SCHED_FIFO or SCHED_RR using:
    //       sched_setscheduler(0, SCHED_FIFO, &param).
    sched_res = sched_setscheduler(0, SCHED_FIFO, &sp);

    // TODO: Verify the updated policy using sched_getscheduler(0).
    if (sched_getscheduler(0) == 1)
        write(STDOUT_FILENO, "works", 5);
    return 0;
}