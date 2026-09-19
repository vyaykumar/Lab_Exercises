#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    char *const envp[] = {NULL};
    char *const args[] = {"ls", "-Rl", NULL};

    // a. execl: path, argument list, NULL
    pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", "-Rl", NULL);
        write(STDERR_FILENO, "execl failed\n", 13);
        _exit(1);
    }
    wait(NULL);

    // b. execlp: filename, argument list, NULL (searches PATH)
    pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", "-Rl", NULL);
        write(STDERR_FILENO, "execlp failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    // c. execle: path, argument list, NULL, environment array
    pid = fork();
    if (pid == 0) {
        execle("/bin/ls", "ls", "-Rl", NULL, envp);
        write(STDERR_FILENO, "execle failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    // d. execv: path, argument array
    pid = fork();
    if (pid == 0) {
        execv("/bin/ls", args);
        write(STDERR_FILENO, "execv failed\n", 13);
        _exit(1);
    }
    wait(NULL);

    // e. execvp: filename, argument array (searches PATH)
    pid = fork();
    if (pid == 0) {
        execvp("ls", args);
        write(STDERR_FILENO, "execvp failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    return 0;
}