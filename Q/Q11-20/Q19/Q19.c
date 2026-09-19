#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main(void) {
    // TODO: Declare struct timespec instances for start and end timestamps.
    struct timespec start, end;

    // TODO: Record start time using clock_gettime(CLOCK_MONOTONIC, &start).
    if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) {
        perror("clock_gettime(start) failed");
        return 1;
    }

    // TODO: Execute getpid().
    int pid = getpid();

    // TODO: Record end time using clock_gettime(CLOCK_MONOTONIC, &end).
    if (clock_gettime(CLOCK_MONOTONIC, &end) < 0) {
        perror ("clock_gettime(end) failed");
        return 1;
    }

    // TODO: Compute elapsed time in nanoseconds:
    //       (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec).
    unsigned long long elapse = (long long) (end.tv_sec - start.tv_sec)* 1000000000ULL +
                                (long long) (end.tv_nsec-start.tv_nsec);

    // TODO: Print the elapsed time.
    printf("Time elapsed for getting PID %d: %llu\n", pid, elapse);

    return 0;
}