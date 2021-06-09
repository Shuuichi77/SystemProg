#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(int argc, char const *argv[])
{
    int file_src, file_dest, r;
    char buffer[BUFFER_SIZE];

    if (argc < 3) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    if ((file_src = open(argv[1], O_RDONLY)) < 0) {
        perror("Error ");
        exit(2);
    }

    if ((file_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
        perror("Error ");
        exit(2);
    }

    while ((r = read(file_src, &buffer, BUFFER_SIZE)) > 0) {
        if (r == -1) {
            perror("Error ");
            exit(3);
        }

        write(file_dest, buffer, BUFFER_SIZE);
    }
    
    close(file_src);
    close(file_dest);

    return EXIT_SUCCESS;
}
