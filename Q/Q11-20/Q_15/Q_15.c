#include <stdio.h>
#include <unistd.h>

extern char **environ;  // Its an array of strings.

int main(void) {
    char **ptr = environ;

    while (*ptr != NULL) {
        printf("%s\n", *ptr);
        ptr++;
    }

    return 0;
}