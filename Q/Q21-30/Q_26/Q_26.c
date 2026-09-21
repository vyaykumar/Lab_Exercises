#include <unistd.h>

int main(void) {
    char *const args[] = {"Q25", NULL};
    char *const envp[] = {NULL};

    execve("../Q25/Q25", args, envp);

    write(STDERR_FILENO, "execve failed\n", 14);
    _exit(1);
}