#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

int main(void) {
    // TODO: Declare struct timespec instances for start and end timestamps.
    struct timespec start, end;

    // TODO: Record start time using clock_gettime(CLOCK_MONOTONIC, &start).
    clock_gettime(CLOCK_MONOTONIC, &start);

    // TODO: Execute getpid().
    int pid = getpid();

    // TODO: Record end time using clock_gettime(CLOCK_MONOTONIC, &end).
    clock_gettime(CLOCK_MONOTONIC, &end);

    // TODO: Compute elapsed time in nanoseconds:
    //       (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec).
    int elapse = (end.tv_sec - start.tv_sec)*1e9 + (end.tv_nsec-start.tv_nsec);

    // TODO: Print the elapsed time.
    printf("Time elpased for getting PID %d: %d", pid, elapse);

    return 0;
}