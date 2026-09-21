#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source>\n", argv[0]);
        return 1;
    }

    const int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror ("open failed");
        return -1;
    }

    char word1[10] = "0123456789";
    if (write(fd, word1, 10) != 10) {
        perror("first write failed");
        close(fd);
        return 1;
    }

    off_t first_off = lseek(fd, 10, SEEK_CUR);
    if (first_off == (off_t)-1) {
        perror("first lseek failed");
        close(fd);
        return 1;
    }
    printf("Offset after seek: %lld\n", (long long)first_off);

    char word2[10] = "abcdefghij";
    if (write(fd, word2, 10) != 10) {
        perror("second write failed");
        close(fd);
        return 1;
    }

    off_t current_off = lseek(fd, 0, SEEK_CUR);
    if (current_off == (off_t)-1) {
        perror("second lseek failed");
        close(fd);
        return 1;
    }
    printf("Offset after second write: %lld\n", (long long)current_off);

    if (current_off != first_off) {
        printf("Offsets are distinct (%lld != %lld).\n",
               (long long)current_off, (long long)first_off);
    }

    close(fd);

    return 0;
}