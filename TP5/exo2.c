#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    char buffer;

    if (pipe(fd) == -1) {
        perror("pipe");
        _exit(2);
    }

    switch(fork()) {
        case -1:
            perror("fork");
            _exit(3);

        case 0:
            close(fd[1]);
            
            while ((read(fd[0], &buffer, 1)) != 0) {
                buffer = toupper(buffer);
                write(STDOUT_FILENO, &buffer, 1);
            };

            write(STDOUT_FILENO, "\n", 1);
            break;
        
        default:
            close(fd[0]);
            
            while ((read(STDIN_FILENO, &buffer, 1)) > 0) {
                write(fd[1], &buffer, 1);
            }

            break;
    }

    return 0;
}