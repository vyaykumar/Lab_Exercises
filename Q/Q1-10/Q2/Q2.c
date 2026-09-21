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
    // TODO: Call mkfifo with the path and file permission bits (e.g. 0666)
    int res = mkfifo(FIFO_PATH, 0666);
    if (res == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }


    // TODO: Open the named pipe with the appropriate access mode (e.g. O_WRONLY or O_RDONLY)
    // TODO: If the file descriptor is negative, handle the open error and exit
    printf("Opening pipe for writing (waiting for a reader)...\n");
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // TODO: Write to or read from the file descriptor using write() or read()
    const char *msg = "Hello through FIFO!\n";
    ssize_t bytes_written = write(fd, msg, strlen(msg));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(1);
    }
    printf("Sent %zd bytes.\n", bytes_written);

    // TODO: Close the file descriptor using close()
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    // TODO: If cleanup is required, remove the named pipe from the filesystem using unlink()
    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
        exit(1);
    }

    return 0;
}
