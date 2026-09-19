#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    // TODO: Call fork() and terminate parent with _exit(0).

    // TODO: Call setsid() to create a new session and detach from controlling terminal.

    // TODO: Call chdir("/") to ensure daemon does not pin any mount points.

    // TODO: Call umask(0) to reset file creation mask.

    // TODO: Close or redirect STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO using open("/dev/null", O_RDWR) and dup2().

    // TODO: Execute the daemon payload loop using sleep() or pause().

    return 0;
}