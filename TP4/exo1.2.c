#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    /* 
    execl -> Tous les arguments 1 par 1
    execv -> Tableau d'arguments
    */
    /* execlp("ls", "ls", argv[1], "-l", NULL); 
    execlp("ls", "ls", NULL);
    printf("ls est terminé\n");

    */

    switch (fork()) {
        case -1:
            perror("Problème fork avec le fils\n");
            break;

        case 0: /* Et après, le fils s'exécute alors qu'on pensait que c'était fini */
            execlp("ls", "ls", NULL);
            break;
        
        default: /* Le père s'exécute en premier */
            wait(NULL); /* Pour attendre que le fils s'exécute avant d'exécuter */
            /* Le wait risque de faire son boulot avant que le fils ait terminé sans le wait */
            printf("Le ls est terminé\n");
            break;
    }
    
    return 0;
}
