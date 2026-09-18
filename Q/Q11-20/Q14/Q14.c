#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and target file path).
    if (argc != 2) {
        printf("Usage: %s <source>", argv[0]);
        return 1;
    }

    // TODO: Declare a struct stat instance.
    struct stat sb;

    // TODO: Call lstat(argv[1], &statbuf) to inspect the file without following symlinks.
    int result = lstat(argv[1], &sb);

    // TODO: Check for errors from lstat.
    if (result < 0) {
        perror("lstat() failed");
        return 1;
    }

    printf("Is source a regular file: \t%d\n",      S_ISREG(sb.st_mode));
    printf("Is source a directory: \t\t%d\n",       S_ISDIR(sb.st_mode));
    printf("Is source a character device: \t%d\n",  S_ISCHR(sb.st_mode));
    printf("Is source a block device: \t%d\n",      S_ISBLK(sb.st_mode));
    printf("Is source a FIFO/Pipe: \t\t%d\n",       S_ISFIFO(sb.st_mode));
    printf("Is source a symlink: \t\t\t%d\n",       S_ISLNK(sb.st_mode));
    printf("Is source a socket: \t\t\t%d\n",        S_ISSOCK(sb.st_mode));

    // TODO: Evaluate statbuf.st_mode using the S_IS* macros:
    //       - S_ISREG(): Regular file
    //       - S_ISDIR(): Directory
    //       - S_ISCHR(): Character device
    //       - S_ISBLK(): Block device
    //       - S_ISFIFO(): FIFO / named pipe
    //       - S_ISLNK(): Symbolic link
    //       - S_ISSOCK(): Socket

    // TODO: Print the identified file type.

    return 0;
}