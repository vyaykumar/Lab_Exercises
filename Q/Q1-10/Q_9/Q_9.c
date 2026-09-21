#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) { fprintf(stderr, "Usage: %s <source>\n", argv[0]); return 1; }

    struct stat sb;

    if (stat(argv[1], &sb)) { perror("stat syscall failed"); return 1; }

    printf("Inode Number:\t\t%lu\n",         sb.st_ino);
    printf("Number of hard links:\t%lu\n",   sb.st_nlink);
    printf("\n");
    printf("Is this a directory:\t%d\n",     S_ISDIR(sb.st_mode));
    printf("Is this a FIFO/pipe:\t%d\n",     S_ISFIFO(sb.st_mode));
    printf("Is this a regular file:\t%d\n",  S_ISREG(sb.st_mode));
    printf("\n");
    printf("File permissions:\t%04o\n",        sb.st_mode & 0777);
    printf("User ID:\t\t%u\n",               sb.st_uid);
    printf("Group ID:\t\t%u\n",              sb.st_gid);
    printf("File size:\t\t%ld\n",            sb.st_size);
    printf("Optimal block size:\t%ld\n",     sb.st_blksize);
    printf("Block count:\t\t%ld\n",          sb.st_blocks);
    printf("\n");
    printf("Last access:\t\t%s",             ctime(&sb.st_atime));
    printf("Last modification:\t%s",         ctime(&sb.st_mtime));
    printf("Last status change:\t%s",        ctime(&sb.st_ctime));

    return 0;
}


// Refer to `man 3type stat`.

// struct stat {
//            dev_t      st_dev;      	 /* ID of device containing file */
//            ino_t      st_ino;      	 /* Inode number */
//            mode_t     st_mode;     	 /* File type and mode */
//            nlink_t    st_nlink;    	 /* Number of hard links */
//            uid_t      st_uid;      	 /* User ID of owner */
//            gid_t      st_gid;      	 /* Group ID of owner */
//            dev_t      st_rdev;     	 /* Device ID (if special file) */
//            off_t      st_size;     	 /* Total size, in bytes */
//            blksize_t  st_blksize;  	 /* Block size for filesystem I/O */
//            blkcnt_t   st_blocks;   	 /* Number of 512 B blocks allocated */
// 
//            struct timespec  st_atim;  /* Time of last access */
//            struct timespec  st_mtim;  /* Time of last modification */
//            struct timespec  st_ctim;  /* Time of last status change */
// };
