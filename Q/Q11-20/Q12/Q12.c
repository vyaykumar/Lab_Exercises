#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).
    if (argc != 2) {
        printf ("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    // TODO: Open the file using custom flags (e.g., O_RDWR | O_APPEND).
    const int fd = open(argv[1], O_RDWR | O_APPEND);
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }
    printf("File Descriptor: %d\n", fd);

    // TODO: Use fcntl(fd, F_GETFL) to retrieve the file status flags.
    auto status = fcntl(fd, F_GETFL);
    if (status == -1) {
        perror("fcntl failed");
        return 1;
    }

    // TODO: Extract the access mode using (flags & O_ACCMODE).
    int access_mode = status & O_ACCMODE;

    // TODO: Compare the result against O_RDONLY, O_WRONLY, and O_RDWR and print the mode.
    switch (access_mode) {
        case O_RDONLY : printf("Access Mode: Read Only (O_RDONLY).\n");  break;
        case O_WRONLY : printf("Access Mode: Write Only (O_WRONLY).\n"); break;
        case O_RDWR :   printf("Access Mode: Read Write (O_RDWR).\n");   break;
        default : printf("Access Mode: Unknown.\n"); break;
    }

    // TODO: Check for optional flags like O_APPEND, O_NONBLOCK, and print their presence.
    if (status & O_APPEND) printf("Flag: O_APPEND is set.\n");
    if (status & O_NONBLOCK) printf("Flag: O_NONBLOCK is set.\n");

    // TODO: Close the file descriptor.
    close(fd);

    return 0;
}