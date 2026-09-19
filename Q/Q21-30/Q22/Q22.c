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
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }

    // TODO: Call fork().
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        close(fd);
        return 1;
    }

    // TODO: In the parent process:
    //       - Write a distinct message string to the open file using write().
    if (pid > 0) {
        char buffer[] = "Hello, from parent process.";
        if (write(fd, buffer, sizeof(buffer)-1) < 0) {
            perror("parent write() failed");
            close(fd);
            return 1;
        }
    }

    // TODO: In the child process:
    //       - Write a distinct message string to the open file using write().
    if (pid == 0) {
        char buffer[] = "Hello, from child process.";
        if (write(fd, buffer, sizeof(buffer)-1) < 0) {
            perror("child write() failed");
            close(fd);
            return 1;
        }
    }

    // TODO: Close the file descriptor using close().
    close(fd);

    return 0;
}