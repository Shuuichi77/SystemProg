#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    int add[2], mul[2], sub[2];
    char exec[128];

    if (pipe(add) == -1) {
        perror("add pipe");
        _exit(1);
    }

    if (pipe(mul) == -1) {
        perror("mul pipe");
        _exit(2);
    }

    if (pipe(sub) == -1) {
        perror("sub pipe");
        _exit(3);
    }

    /* while(1) {
        while ()

    } */

    _exit(0);
}