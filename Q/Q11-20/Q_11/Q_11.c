#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source>\n", argv[0]);
        return 1;
    }

    const int fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }
    printf("File Descriptor: \t\t%d\n", fd);

    const int fd_d1 = dup(fd);
    if (fd_d1 < 0) {
        perror("dup() failed");
        return 1;
    }
    printf("File Descriptor, by dup(): \t%d\n", fd_d1);

    const int target = 114;
    printf("Target FD chosen: \t\t%d\n", target);
    const int fd_d2 = dup2(fd, target);
    if (fd_d2 < 0) {
        perror("dup2() failed");
        return 1;
    }
    printf("File Descriptor, by dup2(): \t%d\n", fd_d2);

    char word1[] = "VIJ";
    ssize_t write1 = write(fd, word1, 3);
    if (write1 < 0) {
        perror("write() failed");
        return 1;
    }

    char word2[] = "AY KU";
    ssize_t write2 = write(fd_d1, word2, 5);
    if (write2 < 0) {
        perror("write() failed");
        return 1;
    }

    char word3[] = "MAR";
    ssize_t write3 = write(fd_d2, word3, 3);
    if (write3 < 0) {
        perror("write() failed");
        return 1;
    }

    close(fd);
    close(fd_d1);
    close(fd_d2);

    return 0;
}