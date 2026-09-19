#include <unistd.h>

int main(int argc, char *argv[]) {
    // TODO: Demonstrate execl("/bin/ls", "ls", "-Rl", NULL).
    execl("/bin/ls", "ls", "-Rl", NULL);

    // TODO: Demonstrate execlp("ls", "ls", "-Rl", NULL).
    execlp("ls", "ls", "-Rl", NULL);

    // TODO: Demonstrate execv("/bin/ls", argv)
    execv("/bin/ls", argv);

    // TODO: Handle failure if exec returns.
    write(STDOUT_FILENO, "exec() failed", 13);
    _exit(1);
}