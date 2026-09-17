#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

const char *PATH = "Q3_output.txt";

int main(int argc, char *argv[]) {
	// TODO: Define the file path and file permissions.

	// TODO: Call the creat system call to create the file.
	int res = creat (PATH, S_IRUSR | S_IWUSR);
	
    // TODO: Check if the file descriptor value is negative.
	if (res < 0) { fprintf (stderr, "Invalid file descriptor.\n"); return -1; }
	
    // TODO: Print the file descriptor value to standard output.
	printf("File descriptor for 'Q3_output.txt' : %d\n", res);
	
    // TODO: Close the file descriptor.
	close(res);
    return 0;
} 
