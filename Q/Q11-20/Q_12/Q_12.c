#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void status_check (const int fd) {
    int status = fcntl(fd, F_GETFL);
    if (status == -1) {
        perror("fcntl(F_GETFL) failed");
        return ;
    }

    int access_mode = status & O_ACCMODE;
    switch (access_mode) {
        case O_RDONLY : printf("Access Mode: Read Only (O_RDONLY).\n");  break;
        case O_WRONLY : printf("Access Mode: Write Only (O_WRONLY).\n"); break;
        case O_RDWR :   printf("Access Mode: Read Write (O_RDWR).\n");   break;
        default : printf("Access Mode: Unknown.\n"); break;
    }

    if (status & O_APPEND) printf("Flag: O_APPEND is set.\n");
    if (status & O_NONBLOCK) printf("Flag: O_NONBLOCK is set.\n");

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf ("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    printf("Testing ReadOnly.\n");
    const int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) { perror("open() failed"); return 1; }
    printf("File Descriptor: %d\n", fd1);
    status_check(fd1);

    printf("Testing WriteOnly, with Append.\n");
    const int fd2 = open(argv[1], O_WRONLY | O_APPEND);
    if (fd2 < 0) { perror("open() failed"); close(fd1); return 1; }
    printf("File Descriptor: %d\n", fd2);
    status_check(fd2);

    printf("Testing ReadWrite, with NonBlock.\n");
    const int fd3 = open(argv[1], O_RDWR | O_NONBLOCK);
    if (fd3 < 0) { perror("open() failed"); close(fd1); close(fd2); return 1; }
    printf("File Descriptor: %d\n", fd3);
    status_check(fd3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}