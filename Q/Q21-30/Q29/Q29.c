#include <unistd.h>
#include <sched.h>
#include <stdio.h>

static void print_policy(int policy) {
    if (policy == SCHED_OTHER) {
        printf("Current policy: SCHED_OTHER\n");
    } else if (policy == SCHED_FIFO) {
        printf("Current policy: SCHED_FIFO\n");
    } else if (policy == SCHED_RR) {
        printf("Current policy: SCHED_RR\n");
    } else {
        printf("Current policy: Unknown (%d)\n", policy);
    }
}

int main(void) {
    int policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler failed");
        return 1;
    }
    print_policy(policy);

    struct sched_param sp;

    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (sp.sched_priority == -1) {
        perror("sched_get_priority_max failed");
        return 1;
    }

    if (sched_setscheduler(0, SCHED_FIFO, &sp) == -1) {
        perror("sched_setscheduler to SCHED_FIFO failed (run with sudo)");
        return 1;
    }
    printf("Switched to SCHED_FIFO.\n");

    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler failed");
        return 1;
    }
    print_policy(policy);

    sp.sched_priority = sched_get_priority_max(SCHED_RR);
    if (sp.sched_priority == -1) {
        perror("sched_get_priority_max failed");
        return 1;
    }

    if (sched_setscheduler(0, SCHED_RR, &sp) == -1) {
        perror("sched_setscheduler to SCHED_RR failed (run with sudo)");
        return 1;
    }
    printf("Switched to SCHED_RR.\n");

    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler failed");
        return 1;
    }
    print_policy(policy);

    return 0;
}