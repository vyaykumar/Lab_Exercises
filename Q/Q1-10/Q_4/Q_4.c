#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

char *Q3_PATH = "../Q_3/Q_3_output.txt";

// Opens a file, validates fd, and returns it.
static int open_file(const char *path, const int flags, const mode_t mode) {
    printf("\n[Attempting open] Path: %s\n", path);
    const int fd = open(path, flags, mode);
    if (fd < 0) {
        perror("open failed");
        printf("errno value: %d\n", errno);
        return -1;
    }
    printf("Successfully opened '%s' (fd: %d)\n", path, fd);
    return fd;
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
