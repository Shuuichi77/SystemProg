#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i, pid, ppid;
    char phrase[128];
    pid_t child;

    for (i = 1 ; i < 21 ; i++) {
        switch(child = fork()) {
            case -1:
                perror("Erreur fils");
                exit(1);
            
            case 0:  
                pid = getpid();
                ppid = getppid();
                sprintf(phrase, "Je suis le numero %d, mon PID est %d et mon pere est %d\n", i, pid, ppid);
                write(STDOUT_FILENO, phrase, strlen(phrase));

                waitpid(-1, &child, 0);
                kill(pid, child);

                if (i == 20) {
                    execlp("ps", "ps", NULL);
                }

                break;

            default:
                for (;;) {
                    pause();
                }
                
                /* printf("Le processus n°%d de PID XXX vient de se terminer\n", waitpid(0, &status, 0)); */
                
                /* sleep(1); 
                exit(0);   */     
        }
    }

    exit(0);
}
