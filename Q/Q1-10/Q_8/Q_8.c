#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s <source>\n", argv[0]);
    	return 1;
    }

	int source = open(argv[1], O_RDONLY);
	if (source < 0) {
		perror("Error opening source file");
		return 1;
	}

	char ch;
	char line[BUFFER_SIZE];
	size_t idx = 0;
	ssize_t bytes_read;

	while ((bytes_read = read(source, &ch, 1)) > 0) {
		line[idx++] = ch;
		if (ch == '\n' || idx == BUFFER_SIZE) {
			ssize_t write_result = write(STDOUT_FILENO, line, idx);
			if (write_result < 0) {
				perror("Error writing to stdout");
				close(source);
				return 1;
			}
			idx = 0;
		}		
	}

	if (bytes_read < 0) {
		perror ("Error reading source file");
		close(source);
		return 1;
	}

	if (idx > 0) {
		if (write(STDOUT_FILENO, line, idx) < 0) {
			perror("Error writing final line");
			close(source);
			return 1;
		}
	}

	close(source);
    return 0;
}
