/* #define _GNU_SOURCE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
/* #include <sys/wait.h> */
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char phrase[128];
    int pid, child_pid, parent_pid;
    /* Printf est bufferisé tant qu'on n'a pas de saut à la ligne : 
    La machine le fait lorsqu'elle aura le temps.
    Ainsi, si on printf dans un fils, et qu'on a pas fait de retour à la ligne dedans, celui-ci meurt
    */ 
    printf("Mon PID est %d", pid = getpid());

    sprintf(phrase, "My PID is %d", pid);
    write(STDOUT_FILENO, phrase, strlen(phrase));
    
    switch(fork()) {
        case -1:
            perror("Error fils");
            exit(1);
        
        case 0:
            printf("Je suis le fils et mon PID est %d", child_pid = getpid());
            sprintf(phrase, "I am the child process and my PID is %d", child_pid);
            write(STDOUT_FILENO, phrase, strlen(phrase));
            break;
        
        default:
            printf("Je suis le fils et mon PID est %d", parent_pid = getpid());
            sprintf(phrase, "I am the parent process and my PID is %d", parent_pid);
            write(STDOUT_FILENO, phrase, strlen(phrase));
            break;
    }

    return 0;
}