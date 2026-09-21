#include <unistd.h>

int main(void) {
    char *const args[] = {"Q_25", NULL};
    char *const envp[] = {NULL};

    execve("../Q_25/Q_25", args, envp);

    write(STDERR_FILENO, "execve failed\n", 14);
    _exit(1);
}