#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

static uint64_t rdtsc(void) {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(void) {
    // struct timespec start, end;

    uint64_t start = rdtsc();

    int pid = getpid();

    uint64_t end = rdtsc();

    unsigned long elapse = (end-start);

    printf("Time elapsed for getting PID %d: %lu\n", pid, elapse);

    return 0;
}