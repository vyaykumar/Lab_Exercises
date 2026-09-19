#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main(void) {
    struct timespec start, end;

    if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) {
        perror("clock_gettime(start) failed");
        return 1;
    }

    int pid = getpid();

    if (clock_gettime(CLOCK_MONOTONIC, &end) < 0) {
        perror ("clock_gettime(end) failed");
        return 1;
    }

    unsigned long long elapse = (long long) (end.tv_sec - start.tv_sec)* 1000000000ULL +
                                (long long) (end.tv_nsec-start.tv_nsec);

    printf("Time elapsed for getting PID %d: %llu\n", pid, elapse);

    return 0;
}