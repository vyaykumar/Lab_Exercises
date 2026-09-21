#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pids[3];
    int sleeps[3] = {2,5,8};

    for (size_t idx = 0; idx < 3; idx++) {
        pids[idx] = fork();
        if (pids[idx] < 0) {
            perror("fork() failed");
            return 1;
        }

        if (pids[idx] == 0) {
            printf("Child %lu (PID: %d) started. Sleeping for %ds...\n",idx + 1, getpid(), sleeps[idx]);
            sleep(sleeps[idx]);
            printf("Child %lu (PID: %d) exiting.\n", idx + 1, getpid());
            _exit(idx+1);
        }
    }

    pid_t target_pid = pids[1];
    int status;
    printf("\nParent waiting for Child 2 (PID: %d) only...\n\n", target_pid);
    pid_t waited_pid = waitpid(target_pid, &status, 0);

    if (waited_pid == -1) {
        perror("waitpid() failed");
        return 1;
    }

    if (WIFEXITED(status))
        printf("Parent reaped Child 2 (PID: %d) with exit code: %d\n",waited_pid, WEXITSTATUS(status));

    while (wait(NULL) > 0) {}

    return 0;
}