#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

int main(void) {
    fd_set set;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    struct timeval timeout;
    timeout.tv_sec = 10;    // seconds.
    timeout.tv_usec = 0;    // microseconds.

    printf("Waiting for input (Timeout of 10seconds)...\n");
    int res = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    if (res == -1) { // Error
        perror ("select() failed");
        return 1;
    }
    else if (res == 0) { // Timeout before fd is ready.
        printf("Timeout: No input received in 10s.\n");
        return 0;
    }
    // Then its ready.


    if (FD_ISSET(STDIN_FILENO, &set)) {
        char buffer[1024];
        const ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer)-1);
        if (bytes_read < 0) {
            perror("read() failed");
            return 1;
        }
        buffer[bytes_read] = '\0';
        printf("Data received (%zd bytes):\n%s", bytes_read, buffer);
    }
    return 0;
}