#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).
    if (argc != 2) { printf("Usage: <source>\n"); return 1; }

    // TODO: Open the target file with O_RDWR | O_CREAT | O_TRUNC, mode 0644.
    const int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror ("open failed");
        printf ("error value: %d", errno);
        return -1;
    }

    // TODO: Write 10 bytes of initial data into the file.
    char word1[10] = "0123456789";
    write(fd, word1, 10);

    // TODO: Use lseek(fd, 10, SEEK_CUR) to move the offset forward by 10 bytes.
    int first_off = lseek(fd, 10, SEEK_CUR);

    // TODO: Write another 10 bytes of data into the file.
    char word2[10] = "abcdefghij";
    write(fd, word2, 10);

    // TODO: Check the return value of lseek to confirm the new file offset.
    if (lseek(fd, 0, SEEK_CUR) != first_off) printf("Offsets are distinct.\n");

    // TODO: Close the file descriptor.
    close(fd);

    return 0;
}