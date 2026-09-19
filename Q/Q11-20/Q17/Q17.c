#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Use
// (set +m; for i in {1..100}; do ./Q17 db.bin > /dev/null & done; wait)
// od -An -td4 db.bin

struct record {
    int ticket_no;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror ("open() failed");
        return 1;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_len = sizeof(struct record);
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl(F_SETLKW) failed");
        close(fd);
        return 1;
    }

    struct record buffer;
    ssize_t bytes_read = read(fd, &buffer, sizeof(struct record));
    if (bytes_read < 0) {
        perror("read() failed");
        close(fd);
        return 1;
    }
    if (bytes_read == 0) {
        buffer.ticket_no = 0;
    }

    buffer.ticket_no++;
    printf("Ticket Number: %d\n", buffer.ticket_no);
    printf("Sleeping for 1 millisecond.\n"); usleep(1000);

    off_t l_res = lseek(fd, 0, SEEK_SET);
    if (l_res == (off_t)-1) {
        perror("lseek() failed");
        close(fd);
        return 1;
    }

    int w_res = write(fd, &buffer, sizeof(struct record));
    if (w_res != sizeof(struct record)) {
        perror("write() failed");
        close(fd);
        return 1;
    }

    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
        perror("fcntl(F_UNLCK) failed");
    else
        printf("File unlocked.\n");

    close(fd);
    return 0;
}