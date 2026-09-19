#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

struct record {
    int record_id;
    int train_no;
};

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and database file path).
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    // TODO: Open the file with O_RDWR.
    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror ("open() failed");
        return 1;
    }

    // TODO: Prompt user for record index to reserve (e.g., 1, 2, or 3).
    int index;
    printf("Enter record index to reserve: ");
    if (scanf("%d", &index) != 1 || index < 1) {
        fprintf(stderr, "Invalid record index.\n");
        close(fd);
        return 1;
    }

    off_t target_offset = (off_t)(index - 1) * sizeof(struct record);
    // TODO: Set struct flock fields targeting only the selected record:
    //       - l_whence = SEEK_SET
    //       - l_start = (record_index - 1) * sizeof(struct record)
    //       - l_len = sizeof(struct record)
    //       - l_type = F_WRLCK
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = target_offset;
    fl.l_len = sizeof(struct record);

    // TODO: Acquire write lock on that specific byte range using fcntl(fd, F_SETLKW, &lock).
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl(F_SETLKW) failed");
        close(fd);
        return 1;
    }

    // TODO: Seek to the selected record's byte offset.
    if (lseek(fd, target_offset, SEEK_SET) == (off_t)-1) {
        perror("lseek() failed");
        close(fd);
        return 1;
    }

    // TODO: Read the record, perform modification, seek back, and write back.
    struct record buffer = {0,0};
    ssize_t bytes_read = read(fd, &buffer, sizeof(struct record));
    if (bytes_read < 0) {
        perror("read() failed");
        close(fd);
        return 1;
    }
    if (bytes_read == 0) {
        buffer.record_id = index;
        buffer.train_no = 1000;
    }

    printf("Current data: Record ID = %d, Train No = %d\n", buffer.record_id, buffer.train_no);

    buffer.record_id = index;
    buffer.train_no += 1;

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
    printf("Updated data: Record ID = %d, Train No = %d\n", buffer.record_id, buffer.train_no);

    // TODO: Unlock the byte range using F_UNLCK.
    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
        perror("fcntl(F_UNLCK) failed");
    else
        printf("Record %d unlocked.\n", index);

    // TODO: Close the file descriptor.
    close(fd);
    return 0;
}