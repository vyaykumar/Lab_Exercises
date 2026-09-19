#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // TODO: Clear errno before calling getpriority().
    errno = 0;

    // TODO: Retrieve current process priority using getpriority(PRIO_PROCESS, 0).
    int priority = getpriority(PRIO_PROCESS, 0);

    // TODO: Print the current niceness value.
    if (priority == -1 && errno != 0) {
        perror ("getpriority() failed");
        return 1;
    }
    printf ("Current priority: %d\n", priority);

    // TODO: Check if an argument was provided to modify priority; if so, parse it.
    int new_priority = 15;
    if (argc == 2) {
        new_priority = atoi(argv[1]);
    }

    // TODO: Alter process priority using nice(increment) or setpriority(PRIO_PROCESS, 0, new_nice).
    priority = setpriority(PRIO_PROCESS, 0, new_priority);
    if (priority < 0) {
        perror("setpriority() failed");
        return 1;
    }

    // TODO: Retrieve the updated priority with getpriority() and verify the change.
    errno = 0;
    priority = getpriority(PRIO_PROCESS, 0);
    // TODO: Print the current niceness value.
    if (priority == -1 && errno != 0) {
        perror ("getpriority() failed");
        return 1;
    }
    printf ("New priority: %d\n", priority);

    return 0;
}
