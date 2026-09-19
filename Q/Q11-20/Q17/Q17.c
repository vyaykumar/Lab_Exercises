#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

struct record {
    int ticket_no;
};

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and database file path).
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    // TODO: Open the binary file with O_RDWR | O_CREAT, mode 0644.
    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror ("open() failed");
        return 1;
    }

    // TODO: Initialise struct flock with F_WRLCK to lock the record segment.
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_len = sizeof(struct record);
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;

    // TODO: Apply the lock using fcntl(fd, F_SETLKW, &lock).
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl(F_SETLKW) failed");
        close(fd);
        return 1;
    }

    // TODO: Read the current struct record from the file using read().
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

    // TODO: Increment the ticket number and print the updated value.
    buffer.ticket_no++;
    printf("Ticket Number: %d\n", buffer.ticket_no);

    // TODO: Seek back to the record position using lseek(fd, 0, SEEK_SET).
    off_t l_res = lseek(fd, 0, SEEK_SET);
    if (l_res == (off_t)-1) {
        perror("lseek() failed");
        close(fd);
        return 1;
    }

    // TODO: Write the updated struct record back using write().
    int w_res = write(fd, &buffer, sizeof(struct record));
    if (w_res != sizeof(struct record)) {
        perror("write() failed");
        close(fd);
        return 1;
    }

    // TODO: Unlock the record with F_UNLCK.
    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
        perror("fcntl(F_UNLCK) failed");
    else
        printf("File unlocked.\n");

    // TODO: Close the file descriptor.
    close(fd);
    return 0;
}