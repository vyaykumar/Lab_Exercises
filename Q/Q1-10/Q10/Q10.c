#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).

    // TODO: Open the target file with O_RDWR | O_CREAT | O_TRUNC, mode 0644.

    // TODO: Write 10 bytes of initial data into the file.

    // TODO: Use lseek(fd, 10, SEEK_CUR) to move the offset forward by 10 bytes.

    // TODO: Write another 10 bytes of data into the file.

    // TODO: Check the return value of lseek to confirm the new file offset.

    // TODO: Close the file descriptor.

    return 0;
}