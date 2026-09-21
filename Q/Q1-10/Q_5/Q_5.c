#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// First made in Q4. with a few tweaks.
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

// Run as background process. append & to the ./Q_5.
int main() {
	int fd[5];
    char path[64];

	for (size_t idx = 0; idx < 5; idx++) {
		snprintf(path, sizeof(path), "temp/temp_%zu.txt", idx+1);
		fd[idx] = open_file(path, O_CREAT | O_RDWR, 0644);
	}	
	
    pid_t pid = getpid();
    printf("Process ID: %d\n", (int)pid);
    printf("Run the following in another terminal:\n");
    printf("  ls -l /proc/%d/fd\n\n", (int)pid);
	
	for (size_t idx = 0; idx < 5; idx++)
		printf("FD for temp_%zu.txt is : %d\n", idx+1, fd[idx]);

	// printf("\nDon't forget to kill.\n");

	printf("Press Enter to exit and cleanup...\n");
	getchar();

    for (size_t idx = 0; idx < 5; idx++)
		if (fd[idx] >= 0) close(fd[idx]);

	printf("File descriptors closed.\n");
    return 0;
}
