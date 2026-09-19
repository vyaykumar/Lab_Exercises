#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // TODO: Check that argc equals 2.
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    // TODO: Open the file with open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644).
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);

    // TODO: Call fork().
    pid_t parent = fork();

    // TODO: In the parent process:
    //       - Write a distinct message string to the open file using write().
    if (parent) {
        char buffer[] = "Hello, from parent process.";
        if (write(fd, buffer, sizeof(buffer)) < 0) {
            perror("parent write() failed");
            return 1;
        }
    }

    // TODO: In the child process:
    //       - Write a distinct message string to the open file using write().
    if (!parent) {
        char buffer[] = "Hello, from child process.";
        if (write(fd, buffer, sizeof(buffer)) < 0) {
            perror("child write() failed");
            return 1;
        }
    }

    // TODO: Close the file descriptor using close().
    close(fd);

    return 0;
}