#include <unistd.h>

int main(void) {
    // TODO: Define the argument array:
    //       char *const args[] = {"/bin/ls", "-l", NULL};
    char *const args[] = {"/bin/ls", "-l", NULL};

    // TODO: Define the environment array:
    //       char *const envp[] = {NULL};
    char *const envp[] = {NULL};

    // TODO: Invoke execve("/bin/ls", args, envp).
    execve("/bin/ls", args, envp);

    // TODO: If execve returns, handle the error using write() or _exit(1).
    write(STDERR_FILENO, "execve failed\n", 14);
    _exit(1);
}