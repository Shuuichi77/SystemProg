#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i = 5;
    printf("Avant: i = %d, adresse = %p\n", i, &i);
    
    switch(fork()) {
        case -1:
            perror("Erreur fils");
            exit(1);
        
        case 0: 
            i = 6;
            printf("Fils : i = %d, adresse = %p\n", i, &i); 
            /* Il ne renvoie pas la vraie adresse, on a la même que le 1er i pour être cohérent :
            quand je fork, j'hérite de toutes mes variables qui restent modifiable 
            Problème si on a un pointeur qui pointeraient sur la même chose */
            break;

        default:
            i = 7;
            printf("Pere : i = %d, adresse = %p\n", i, &i);
            break;
    }

    return 0;
}
