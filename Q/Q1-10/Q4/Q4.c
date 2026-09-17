#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

char *Q3_PATH = "../Q3/Q3_output.txt";

// Opens a file, checks it, and returns its fd.
int open_file (const char* path, int flags ,mode_t mode) {
	printf ("\nInside open() wrapper.\n");
	int res = open (path, flags, mode);
	if (res < 0) {
		perror("open failed");
		printf("errno value: %d\n", errno);
		return -1;
	}
	printf("%s opened successfully with mode %o.\n\n", path, mode);
	return res;
}

int main() {

	// int res = open (Q3_PATH, O_RDWR);
	// if (res < 0) {
	// 	perror("open with O_RDWR failed.\n");
	// 	printf("errno value: %d\n", errno);
	// 	return -1;
	// }
	// printf("Q3_output opened successfully with O_RDWR.\n");
	// close(res);
	int res = open_file (Q3_PATH, O_RDWR, 0);
	if (res != -1) 
		printf("Q3_output opened successfully with O_RDWR.\n");	// This is redundant.
	close(res);
	
	// res = open (Q3_PATH, O_RDWR | O_EXCL);
	// if (res < 0) {
	// 	perror("open with O_RDWR and O_EXCL failed.\n");
	// 	printf("errno value: %d\n", errno);
	// 	return -1;
	// }
	// printf("Q3_output opened successfully with O_RDWR and O_EXCL.\n");
	// close (res);
	close (open_file(Q3_PATH, O_RDWR | O_EXCL, 0644));

	res = open_file(Q3_PATH, O_CREAT | O_EXCL, 0644);
	if (res != -1) 
		printf("Q3_output opened successfully with O_CREAT and O_EXCL.\n");
	close(res);
		
    return 0;
}
