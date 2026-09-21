#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    while (1) {
        const ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

        if (bytes_read == -1) {
            if (errno == EINTR)
                continue;
            perror("Read failed");
            return EXIT_FAILURE;
        }

        if (bytes_read == 0)
            break;

        ssize_t total_written = 0;
        while (total_written < bytes_read) {
            ssize_t bytes_written = write(STDOUT_FILENO,
                                          buffer + total_written,
                                          bytes_read - total_written);
            if (bytes_written == -1) {
                if (errno == EINTR)
                    continue;
                perror("Write failed");
                return EXIT_FAILURE;
            }
            total_written += bytes_written;
        }
    }
		
    return EXIT_SUCCESS;
}
