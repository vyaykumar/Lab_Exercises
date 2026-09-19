#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, 0);
    if (priority == -1 && errno != 0) {
        perror ("getpriority() failed");
        return 1;
    }
    printf ("Current priority: %d\n", priority);

    int increment = 5;
    if (argc == 2)
        increment = atoi(argv[1]);

    errno = 0;
    int ret = nice(increment);
    if (ret == -1 && errno != 0) {
        perror("nice() failed");
        return 1;
    }

    errno = 0;
    priority = getpriority(PRIO_PROCESS, 0);
    if (priority == -1 && errno != 0) {
        perror ("getpriority() failed");
        return 1;
    }
    printf ("New priority: %d\n", priority);

    return 0;
}
