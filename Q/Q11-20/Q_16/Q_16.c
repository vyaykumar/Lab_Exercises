#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;
    // fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;     // Relative to file start.
    fl.l_start = 0;             // Start offset
    fl.l_len = 0;               // To EOF
    fl.l_pid = getpid();

    // F_SETLK for NonBlocking lock
    // F_SETLKW for Blocking lock
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        if (errno == EAGAIN || errno == EACCES) {
            printf("File is locked by another process.\n");
            printf("Waiting with blocking F_SETLKW.\n");

            if (fcntl(fd, F_SETLKW, &fl) == -1) {
                perror ("fcntl(F_SETLKW) failed");
                close(fd);
                return 1;
            }
        }
        else {
            perror ("fcntl(F_SETLK) failed");
            close(fd);
            return 1;
        }
    }

    printf("Lock acquired for PID %d\n", fl.l_pid);

    printf("Press any key to release the lock and exit...\n");
    fflush(stdout);
    getchar();

    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
        perror("fcnctl(F_UNLCK) failed");
    else
        printf("Lock released.\n");

    close(fd);
    return 0;
}