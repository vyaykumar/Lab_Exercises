#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd failed");
        return 1;
    }

    char script_path[PATH_MAX];
    snprintf(script_path, sizeof(script_path), "%s/task.sh", cwd);

    // TODO: Call fork() and terminate parent with _exit(0).
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork()");
        return 1;
    }

    if (pid != 0) {
        _exit(0);
    }

    // TODO: Call setsid() to create a new session and detach from controlling terminal.
    if (setsid() == -1) {
        _exit(1);
    }

    // TODO: Call chdir("/") to ensure daemon does not pin any mount points.
    if (chdir("/") == -1) {
        _exit(1);
    }

    // TODO: Call umask(0) to reset file creation mask.
    umask(0);

    // TODO: Close or redirect STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO using open("/dev/null", O_RDWR) and dup2().
    int dev_null = open("/dev/null", O_RDWR);
    if (dev_null == -1) {
        _exit(1);
    }

    dup2(dev_null, STDIN_FILENO);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);

    if (dev_null > STDERR_FILENO) {
        close(dev_null);
    }

    sleep(10);

    if (chdir(cwd) == -1) {
        _exit(1);
    }

    // TODO: Execute the daemon payload loop using sleep() or pause().
    execlp("x-terminal-emulator", "x-terminal-emulator", "-e", "/bin/sh", script_path, NULL);
    execl("/bin/sh", "sh", script_path, NULL);

    return 0;
}