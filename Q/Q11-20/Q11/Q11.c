#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).

    // TODO: Open the file with O_RDWR | O_CREAT | O_APPEND, mode 0644.

    // TODO: Duplicate the file descriptor using dup().

    // TODO: Duplicate the original descriptor to a specific target number using dup2().

    // TODO: Write text using the original descriptor.

    // TODO: Write text using the dup() descriptor.

    // TODO: Write text using the dup2() descriptor.

    // TODO: Close all three file descriptors.

    return 0;
}