/* #define _GNU_SOURCE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
/* #include <sys/wait.h> */
#include <unistd.h>

int main(int argc, char const *argv[])
{
    
    switch(fork()) {
        case -1:
            perror("Fils erroné ");
            exit(1);
        
        case 0:
            printf("Fils\n");
            exit(0);

        default:
            
            break;
    }

    return 0;
}
