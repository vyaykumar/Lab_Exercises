#include <unistd.h>
#include <sched.h>

int main(void) {
    // TODO: Get current scheduling policy using sched_getscheduler(0).

    // TODO: Declare and set struct sched_param.
    //       - param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    // TODO: Change policy to SCHED_FIFO or SCHED_RR using:
    //       sched_setscheduler(0, SCHED_FIFO, &param).

    // TODO: Verify the updated policy using sched_getscheduler(0).

    return 0;
}