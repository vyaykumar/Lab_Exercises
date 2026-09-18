#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and target file path).

    // TODO: Declare a struct stat instance.

    // TODO: Call lstat(argv[1], &statbuf) to inspect the file without following symlinks.

    // TODO: Check for errors from lstat.

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