#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// First made in Q4. with a few tweaks.
int open_file (const char* path, int flags ,mode_t mode) {
	// printf ("Inside open() wrapper.\n");
	int res = open (path, flags, mode);
	if (res < 0) {
		perror("open failed");
		printf("errno value: %d\n", errno);
		return -1;
	}
	printf("%s opened successfully with mode %o.\n", path, mode);
	return res;
}

// Run as background process. append & to the ./Q5.
int main() {
	int fd[5];
		
    char path[64];
	for (size_t idx = 0; idx < 5; idx++) {
		snprintf(path, sizeof(path), "Q5_temp_files/temp_%zu.txt", idx+1);
		fd[idx] = open_file(path, O_CREAT | O_RDWR, 0644);
	}	
	
    printf("\nProcess ID: %d\n", (int)getpid());
	printf("\nRun the following: \nls -l /proc/%d/fd\n\n", (int)getpid());
	
	for (size_t idx = 0; idx < 5; idx++)
		printf("FD for temp_%zu.txt is : %d\n", idx+1, fd[idx]);

	// printf("\nDon't forget to kill.\n");

	printf("Press any key to exit and cleanup...\n");
	getchar();

    for (size_t idx = 0; idx < 5; idx++)
		if (fd[idx] >= 0) close(fd[idx]);

	printf("File descriptors closed.\n");

    return 0;
}
