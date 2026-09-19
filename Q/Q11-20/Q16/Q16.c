#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and file path).
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    // TODO: Open the file with O_RDWR.
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open() failed");
        return 1;
    }

    // TODO: Declare and initialise a struct flock instance:
    //       - l_type: F_WRLCK (or F_RDLCK)
    //       - l_whence: SEEK_SET
    //       - l_start: 0
    //       - l_len: 0 (lock whole file)
    //       - l_pid: getpid()
    struct flock fl;
    fl.l_type = F_WRLCK;
    // fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    // TODO: Call fcntl(fd, F_SETLK, &lock) for non-blocking or F_SETLKW for blocking.
    // F_SETLK for NonBlocking lock
    // F_SETLKW for Blocking lock
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        // TODO: Check if the lock was acquired or if an error occurred (e.g., EACCES, EAGAIN).
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

    // TODO: Simulate a critical section (e.g., sleep or prompt user input).
    printf("Press any key to release the lock and exit...\n");
    fflush(stdout);
    getchar();

    // TODO: Release the lock by setting l_type = F_UNLCK and calling fcntl().
    fl.l_type = F_UNLCK;
    if (fcnctl(fd, F_SETLK, &fl) == -1)
        perror("fcnctl(F_UNLCK) failed");
    else
        printf("Lock released.\n");

    // TODO: Close the file descriptor.
    close(fd);
    return 0;
}