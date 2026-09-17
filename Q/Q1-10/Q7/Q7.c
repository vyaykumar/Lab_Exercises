#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 3 (program name, source file, destination file).
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
		return -1;
	}
	
    // TODO: Open the source file (argv[1]) in read-only mode (O_RDONLY).
	int source = open (argv[1], O_RDONLY);
	if (source < 0) {
		perror("Error opening source file");
		return 1;
	}
	
    // TODO: Open/create the destination file (argv[2]) with write permissions (O_WRONLY | O_CREAT | O_TRUNC, 0644).
	int destination = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (destination < 0) {
		perror("Error opening destination file");
		close(source);
		return 1;
	}
	
    // TODO: Declare a buffer of size BUFFER_SIZE and a variable of type ssize_t for bytes read.
	char buffer[BUFFER_SIZE];
	
    // TODO: Loop while read() returns bytes from the source file descriptor.
    ssize_t bytes_read;
	while ((bytes_read = read(source, buffer, BUFFER_SIZE)) > 0) {
		// TODO: Inside the loop, write() the read bytes to the destination file descriptor.
		ssize_t write_res = write(destination, buffer, (size_t)bytes_read);
		if (write_res < 0) {
			perror("Error writing to destination file");
			close(source);
			close(destination);
			return -1;
		}
	}
    // TODO: Check for read/write errors.
	if (bytes_read < 0) {
		perror("Error reading source file");
		close(source);
		close(destination);
		return 1;
	}
    // TODO: Close both file descriptors.
	close(source);
	close(destination);
	
    return 0;
}

/*
 * ============================================================================
 * VIVA QUESTIONS FOR Q7 (File Copy Implementation)
 * ============================================================================
 *
 * 1. System Call Fundamentals & Flags:
 *    - Why is the mode argument (e.g., 0644) mandatory when O_CREAT is set,
 *      and what happens if it is omitted in open()?
 *    - What is the role of O_TRUNC in this program? What would happen if the
 *      destination file already existed with 5000 bytes, but the source file
 *      contained only 100 bytes?
 *    - How does the process umask interact with the mode argument 0644 during
 *      file creation?
 *
 * 2. Return Values & Error Handling:
 *    - Why is bytes_read declared as ssize_t instead of size_t or int?
 *    - What exact values can read() return, and what does each return value signify?
 *    - If the read loop condition were `while (bytes_read = read(...))`, what would
 *      happen if read encountered a hardware read error and returned -1?
 *    - In what situations can write() successfully write fewer bytes than requested
 *      (a partial write), and how should a production copy program handle that?
 *
 * 3. File Descriptors & Resource Management:
 *    - If open() for destination fails, why must we explicitly close the source file
 *      descriptor before returning, rather than just returning immediately?
 *    - What happens to open file descriptors if a program terminates abruptly
 *      via exit() or a fatal signal? Why is manual cleanup still considered good practice?
 *    - What error is set in errno if the system-wide or per-process file descriptor
 *      limit is exceeded during open()?
 *
 * 4. Buffering & Performance:
 *    - How does BUFFER_SIZE affect the number of user-to-kernel context switches?
 *    - Is there any performance difference between copying with a 1024-byte buffer
 *      versus an 8192-byte buffer? How does the filesystem block size relate to this?
 *    - How does this implementation compare in behavior and efficiency to the standard
 *      C library functions fopen(), fread(), fwrite(), and fclose()?
 * ============================================================================
 */
