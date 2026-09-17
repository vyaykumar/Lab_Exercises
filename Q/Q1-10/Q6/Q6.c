#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
	ssize_t n_bytes;
	
	while ((n_bytes = read (STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		ssize_t res = write (STDOUT_FILENO, buffer, n_bytes);
		if (res == -1) {
			perror("Write failed");
			return -1;
		}
	}

	if (n_bytes == -1) {
		perror("Read failed");
		return -1;
	}
		
    return 0;
}
