#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *PATH = "Q_3_output.txt";

	int res = creat (PATH, S_IRUSR | S_IWUSR);

	if (res < 0) { perror("creat() failed"); return -1; }

	printf("File descriptor for 'Q3_output.txt' : %d\n", res);

	close(res);
    return 0;
} 
