#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    char *const envp[] = {NULL};
    char *const args[] = {"ls", "-Rl", NULL};

    pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", "-Rl", NULL);
        write(STDERR_FILENO, "execl failed\n", 13);
        _exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", "-Rl", NULL);
        write(STDERR_FILENO, "execlp failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        execle("/bin/ls", "ls", "-Rl", NULL, envp);
        write(STDERR_FILENO, "execle failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        execv("/bin/ls", args);
        write(STDERR_FILENO, "execv failed\n", 13);
        _exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        execvp("ls", args);
        write(STDERR_FILENO, "execvp failed\n", 14);
        _exit(1);
    }
    wait(NULL);

    return 0;
}