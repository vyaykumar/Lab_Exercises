#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define FIFO_PATH "my_pipe"
#define BUFFER_SIZE 256

int main(void) {
    int res = mkfifo(FIFO_PATH, 0666);
    if (res == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }

    printf("Opening pipe for reading (waiting for a writer)...\n");
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s", buffer);
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}