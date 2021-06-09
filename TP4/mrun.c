#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{   
    char var[6] = "RUN_0", *pt = NULL;

    while (NULL != (pt = getenv(var))) {
        switch(fork()) {
            case -1:
                perror("Problème fils mort (fork)");
                break;

            case 0:
                printf("Execute \"%s\" :\n", pt);
                argv[0] = pt;
                execvp(pt, argv);
                break;

            default:
                wait(NULL);
                printf("\n");
                break;
        }


        var[4]++;
    }

    return 0;
}
