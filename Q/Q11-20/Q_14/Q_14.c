#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 1;
    }

    struct stat sb;

    int result = lstat(argv[1], &sb);

    if (result < 0) {
        perror("lstat() failed");
        return 1;
    }

    char *type = "Unknown";

    if (S_ISREG(sb.st_mode))        type = "Regular File";
    else if (S_ISDIR(sb.st_mode))   type = "Directory";
    else if (S_ISCHR(sb.st_mode))   type = "Character Device";  // Use /dev/null as argument.
    else if (S_ISBLK(sb.st_mode))   type = "Block Device";      // Use /dev/sda  as argument.
    else if (S_ISFIFO(sb.st_mode))  type = "FIFO/Pipe";         // Can't make one for some reason.
    else if (S_ISLNK(sb.st_mode))   type = "Symlink";
    else if (S_ISSOCK(sb.st_mode))  type = "Socket";            // Use /run/systemd/private.

    printf("File: %s\n", argv[1]);
    printf("Type: %s\n", type);

    return 0;
}