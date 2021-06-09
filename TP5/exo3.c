#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void child_handler(int signal) {
    printf("Printf child handler\n");
}

void pipe_handler(int signal) {
    printf("Printf pipe handler\n");
}

int main(int argc, char const *argv[])
{
    int fd[2], i;
    char buffer;

    if (pipe(fd) == -1) {
        perror("pipe");
        _exit(1);
    }

    signal(SIGCHLD, child_handler);
    signal(SIGPIPE, pipe_handler);

    switch(fork()) {
        case -1:
            perror("fork");
            _exit(2);

        case 0:
            close(fd[1]);
            
            while ((read(fd[0], &buffer, 1)) != 0 && i < 10) {
                buffer = toupper(buffer);
                write(STDOUT_FILENO, &buffer, 1);
                i++;
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

    _exit(0);
}