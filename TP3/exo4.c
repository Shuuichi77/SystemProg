#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char const *argv[])
{
    char buffer[BUFFER_SIZE];
    int file_src;

    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    if ((file_src = open(argv[1], O_RDONLY)) < 0) {
        perror("Error ");
        exit(2);
    }

    dup2(file_src, STDIN_FILENO);

    while (scanf("%s", buffer) == 1) {
        printf("J'ai lu %s\n", buffer);
    }

    close(file_src);

    return EXIT_SUCCESS;
}
