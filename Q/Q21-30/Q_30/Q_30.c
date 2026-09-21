#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        return 1;
    }

    char script_path[PATH_MAX + 16];
    snprintf(script_path, sizeof(script_path), "%s/task.sh", cwd);

    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    }
    if (pid > 0) {
        _exit(0);
    }

    if (setsid() < 0) {
        _exit(1);
    }

    umask(0);

    if (chdir(cwd) < 0) {
        _exit(1);
    }

    int log_fd = open("daemon_output.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_fd >= 0) {
        dup2(log_fd, STDOUT_FILENO);
        dup2(log_fd, STDERR_FILENO);
        if (log_fd > STDERR_FILENO) {
            close(log_fd);
        }
    }

    int dev_null = open("/dev/null", O_RDONLY);
    if (dev_null >= 0) {
        dup2(dev_null, STDIN_FILENO);
        if (dev_null > STDERR_FILENO) {
            close(dev_null);
        }
    }

    sleep(2);

    execl("/bin/sh", "sh", script_path, NULL);
    _exit(1);
}