#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // TODO: Verify that argc equals 2 (program name and target file path).

    // TODO: Declare a struct stat instance to hold file metadata.

    // TODO: Call stat(argv[1], &file_stat) and check for errors.

    // TODO: Print the Inode number (st_ino).

    // TODO: Print the Number of hard links (st_nlink).

    // TODO: Determine and print the file type (regular file, directory, symlink, etc.) using S_IS* macros.

    // TODO: Print raw octal permissions (st_mode & 0777).

    // TODO: Print UID (st_uid) and GID (st_gid).

    // TODO: Print file size in bytes (st_size).

    // TODO: Print optimal block size (st_blksize) and block count (st_blocks).

    // TODO: Format and print timestamps (st_atime, st_mtime, st_ctime) using ctime().

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
