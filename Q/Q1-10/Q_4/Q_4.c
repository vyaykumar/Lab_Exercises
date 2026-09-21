#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static char* Q3_PATH = "../Q_3/Q_3_output.txt";

// Opens a file, validates fd, and returns it.
static int open_file(const char *path, const int flags, const mode_t mode) {
    printf("\n[Attempting open] Path: %s\n", path);
    const int fd = open(path, flags, mode);
    if (fd < 0) {
        perror("open failed");
        printf("errno value: %d\n", errno);
        return -1;
    }
    printf("Successfully opened '%s' (fd: %d)\n", path, fd);
    return fd;
}

int main() {
    // The usual
    int fd = open_file(Q3_PATH, O_RDWR, 0);
    if (fd >= 0)
        close(fd);

    // O_RDWR | O_EXCL
    fd = open_file(Q3_PATH, O_RDWR | O_EXCL, 0);
    if (fd >= 0)
        close(fd);

    // Previous with O_CREAT
    fd = open_file(Q3_PATH, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd >= 0) {
        printf("File created exclusively.\n");
        close(fd);
    } else if (errno == EEXIST)
        printf("Expected error: File already exists (EEXIST).\n");

    return 0;
}
