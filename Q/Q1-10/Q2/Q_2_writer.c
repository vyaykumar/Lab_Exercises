#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FIFO_PATH "my_pipe"

int main(void) {
    int res = mkfifo(FIFO_PATH, 0666);
    if (res == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }

    printf("Opening pipe for writing (waiting for a reader)...\n");
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    const char *msg = "Hello through FIFO!\n";
    ssize_t bytes_written = write(fd, msg, strlen(msg));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(1);
    }
    printf("Sent %zd bytes.\n", bytes_written);

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
        exit(1);
    }

    return 0;
}
