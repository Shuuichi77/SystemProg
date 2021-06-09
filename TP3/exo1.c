#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1048576

int main(int argc, char const *argv[])
{
    int fd, i, size;
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        write(STDERR_FILENO, "Not enough arguments\n", 22);
        exit(1);
    }

    for (i = 1 ; i < argc ; i++) {
        if ((fd = open(argv[i], O_RDONLY)) == -1) {
            perror("Error open()");
            exit(2);
        }

        if ((size = read(fd, buffer, BUFFER_SIZE)) == -1) {
            perror("Error read()");
            exit(3);
        }

        write(STDOUT_FILENO, buffer, size);
    }

    close(fd);


    return 0;
}
