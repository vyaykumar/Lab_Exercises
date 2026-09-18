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

    // TODO: Evaluate statbuf.st_mode using the S_IS* macros:
    //       - S_ISREG(): Regular file
    //       - S_ISDIR(): Directory
    //       - S_ISCHR(): Character device
    //       - S_ISBLK(): Block device
    //       - S_ISFIFO(): FIFO / named pipe
    //       - S_ISLNK(): Symbolic link
    //       - S_ISSOCK(): Socket

    char *type = "Unknown";

    if (S_ISREG(sb.st_mode)) type = "Regular File";
    else if (S_ISDIR(sb.st_mode)) type = "Directory";
    else if (S_ISCHR(sb.st_mode)) type = "Character Device";
    else if (S_ISBLK(sb.st_mode)) type = "Block Device";
    else if (S_ISFIFO(sb.st_mode)) type = "FIFO/Pipe";
    else if (S_ISLNK(sb.st_mode)) type = "Symlink";
    else if (S_ISSOCK(sb.st_mode)) type = "Socket";

    // TODO: Print the identified file type.
    printf("File: %s", argv[1]);
    printf("Type: %s", type);

    return 0;
}