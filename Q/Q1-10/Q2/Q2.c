#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    // TODO: Call mkfifo with the path and file permission bits (e.g. 0666)
	int res = mkfifo("my_pipe", 0666);
	
    // TODO: If mkfifo returns -1 and errno is not EEXIST, print an error and exit
	if (res == -1 && errno != EEXIST) { perror("mkfifo\n"); exit(1); }

    // TODO: Open the named pipe with the appropriate access mode (e.g. O_WRONLY or O_RDONLY)
	open ()
    // TODO: If the file descriptor is negative, handle the open error and exit

    // TODO: Write to or read from the file descriptor using write() or read()

    // TODO: Close the file descriptor using close()

    // TODO: If cleanup is required, remove the named pipe from the filesystem using unlink()

    return 0;
}
