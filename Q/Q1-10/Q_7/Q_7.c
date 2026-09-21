#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
		return 1;
	}

	int source = open (argv[1], O_RDONLY);
	if (source < 0) {
		perror("Error opening source file");
		return 1;
	}

	int destination = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (destination < 0) {
		perror("Error opening destination file");
		close(source);
		return 1;
	}

	char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

	while ((bytes_read = read(source, buffer, BUFFER_SIZE)) > 0) {
		const ssize_t write_res = write(destination, buffer, (size_t)bytes_read);
		if (write_res < 0) {
			perror("Error writing to destination file");
			close(source);
			close(destination);
			return 1;
		}
	}
	if (bytes_read < 0) {
		perror("Error reading source file");
		close(source);
		close(destination);
		return 1;
	}

	close(source);
	close(destination);
	
    return 0;
}

