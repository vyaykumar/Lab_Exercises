#include <unistd.h>

int main(void) {
    char *const args[] = {"/bin/ls", "-l", NULL};

    char *const envp[] = {NULL};

    execve("/bin/ls", args, envp);

    write(STDERR_FILENO, "execve failed\n", 14);
    _exit(1);
}