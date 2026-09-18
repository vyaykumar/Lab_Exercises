#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

int main(void) {
    // TODO: Declare an fd_set variable.
    fd_set set;

    // TODO: Clear the set with FD_ZERO() and add STDIN_FILENO with FD_SET().
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    // TODO: Declare and set a struct timeval instance for a 10-second timeout.
    // struct timeval timeout; Don't know how to initialize.

    // TODO: Call select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout).
    auto res = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    // TODO: Check the return value of select (error, timeout, or ready).
    // if (res == ) Don't know the output values.

    // TODO: If ready, confirm with FD_ISSET() and read the input using read().

    return 0;
}