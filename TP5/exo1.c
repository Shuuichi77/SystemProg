#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd[2];

    if (argc != 3) {
        write(STDERR_FILENO, "Need 2 arguments\n", 17);
        _exit(1);
    }

    if (pipe(fd) == -1) {
        _exit(2);
    }

    switch(fork()) {
        case -1:
            write(STDERR_FILENO, "Fork error\n", 11);
            _exit(3);

        case 0:
            close(fd[0]);
            dup2(fd[1], 1); /* 1 = stdout */
            execlp(argv[1], argv[1], NULL);
            break;
        
        default:
            close(fd[1]);

            if (dup2(fd[0], 0) == -1) { /* 0 = stdin */
                _exit(3);
            }

            execlp(argv[2], argv[2], NULL);
            _exit(4);
            break;
    }

    return 0;
}