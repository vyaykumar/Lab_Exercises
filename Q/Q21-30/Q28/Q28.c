#include <unistd.h>
#include <sched.h>
#include <stdio.h>

int main(void) {
    int max_fifo = sched_get_priority_max(SCHED_FIFO);
    int min_fifo = sched_get_priority_min(SCHED_FIFO);

    if (max_fifo == -1 || min_fifo == -1) {
        perror("sched_get_priority for SCHED_FIFO failed");
        return 1;
    }

    int max_rr = sched_get_priority_max(SCHED_RR);
    int min_rr = sched_get_priority_min(SCHED_RR);

    if (max_rr == -1 || min_rr == -1) {
        perror("sched_get_priority for SCHED_RR failed");
        return 1;
    }

    printf("SCHED_FIFO Priority Range: Min = %d, Max = %d\n", min_fifo, max_fifo);
    printf("SCHED_RR   Priority Range: Min = %d, Max = %d\n", min_rr, max_rr);

    return 0;
}
