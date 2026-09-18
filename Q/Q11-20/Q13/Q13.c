#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).

    // TODO: Open the file using custom flags (e.g., O_RDWR | O_APPEND).

    // TODO: Use fcntl(fd, F_GETFL) to retrieve the file status flags.

    // TODO: Extract the access mode using (flags & O_ACCMODE).

    // TODO: Compare the result against O_RDONLY, O_WRONLY, and O_RDWR and print the mode.

    // TODO: Check for optional flags like O_APPEND, O_NONBLOCK, and print their presence.

    // TODO: Close the file descriptor.

    return 0;
}