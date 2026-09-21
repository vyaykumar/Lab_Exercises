#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        close(fd);
        return 1;
    }

    if (pid > 0) {
        char buffer[] = "Hello, from parent process.\n";
        if (write(fd, buffer, sizeof(buffer)-1) < 0) {
            perror("parent write() failed");
            close(fd);
            return 1;
        }
    }

    if (pid == 0) {
        char buffer[] = "Hello, from child process.\n";
        if (write(fd, buffer, sizeof(buffer)-1) < 0) {
            perror("child write() failed");
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}