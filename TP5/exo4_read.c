#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    int res;
    char c;

    if (-1 == (res = open("./exo4_pipe", O_RDONLY))) {
        perror("open error");
        _exit(1);
    }

    dup2(res, STDIN_FILENO);
    close(res);

    while(read(STDIN_FILENO, &c, 1) != 0) {
        c = toupper(c);
        write(STDOUT_FILENO, &c, 1);
    }

    _exit(0);
}