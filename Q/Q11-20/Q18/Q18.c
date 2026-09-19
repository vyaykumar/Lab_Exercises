#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct record {
        int record_id;
        int ticket_no;
    };

    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror ("open() failed");
        return 1;
    }

    int index;
    printf("Enter record index to reserve: ");
    if (scanf("%d", &index) != 1 || index < 1) {
        fprintf(stderr, "Invalid record index.\n");
        close(fd);
        return 1;
    }

    off_t target_offset = (off_t)(index - 1) * sizeof(struct record);
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = target_offset;
    fl.l_len = sizeof(struct record);

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl(F_SETLKW) failed");
        close(fd);
        return 1;
    }

    if (lseek(fd, target_offset, SEEK_SET) == (off_t)-1) {
        perror("lseek() failed");
        close(fd);
        return 1;
    }

    struct record buffer = {0,0};
    ssize_t bytes_read = read(fd, &buffer, sizeof(struct record));
    if (bytes_read < 0) {
        perror("read() failed");
        close(fd);
        return 1;
    }
    if (bytes_read == 0) {
        buffer.record_id = index;
        buffer.ticket_no = 1000;
    }

    printf("Current data: Record ID = %d, Train No = %d\n", buffer.record_id, buffer.ticket_no);

    buffer.record_id = index;
    buffer.ticket_no += 1;

    if (lseek(fd, target_offset, SEEK_SET) == (off_t)-1) {
        perror("lseek write failed");
        close(fd);
        return 1;
    }

    if (write(fd, &buffer, sizeof(struct record)) != sizeof(struct record)) {
        perror("write failed");
        close(fd);
        return 1;
    }
    printf("Updated data: Record ID = %d, Ticket No = %d\n", buffer.record_id, buffer.ticket_no);

    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
        perror("fcntl(F_UNLCK) failed");
    else
        printf("Record %d unlocked.\n", index);

    close(fd);
    return 0;
}