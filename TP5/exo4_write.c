#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    int res;
    char c;

    if (-1 == (res = open("./exo4_pipe", O_WRONLY))) {
        perror("open error");
        _exit(1);
    }

    dup2(STDIN_FILENO, res);

    while(read(STDIN_FILENO, &c, 1) != 0) {
        write(STDIN_FILENO, &c, 1);
    }


    _exit(0);
}