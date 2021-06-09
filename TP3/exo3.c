#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int file_dest;

    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    if ((file_dest = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
        perror("Error ");
        exit(2);
    }

    dup2(file_dest, STDOUT_FILENO);
    
    printf("Ceci est un premier test\n");
    printf("Ceci est un second test\n");
    printf("ejhfezfhejzfezfjihezj\n");

    close(file_dest);

    return EXIT_SUCCESS;
}
