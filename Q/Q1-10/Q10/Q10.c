#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: <source>\n"); return 1; }

    const int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror ("open failed");
        printf ("error value: %d", errno);
        return -1;
    }

    char word1[10] = "0123456789";
    write(fd, word1, 10);

    int first_off = lseek(fd, 10, SEEK_CUR);

    char word2[10] = "abcdefghij";
    write(fd, word2, 10);

    if (lseek(fd, 0, SEEK_CUR) != first_off) printf("Offsets are distinct.\n");

    close(fd);

    return 0;
}