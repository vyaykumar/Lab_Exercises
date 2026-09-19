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

    int new_priority = 15;
    if (argc == 2)
        new_priority = atoi(argv[1]);

    priority = setpriority(PRIO_PROCESS, 0, new_priority);
    if (priority < 0) {
        perror("setpriority() failed");
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
