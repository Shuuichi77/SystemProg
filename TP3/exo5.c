#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1
#define NB_OPTION 3

typedef enum {
    IS_A_CHARACTER,
    IS_A_SPACE,
    IS_A_NEWLINE
} CharacterType;

typedef enum {
    l,
    w,
    c
} Options;

int main(int argc, char * const argv[]) {
    int options[NB_OPTION];
    int file_src, nb_option = 0, res, i, last_char = -1, nb_mot = 0, nb_char = 0, nb_ligne = 0;
    char buffer[BUFFER_SIZE];
    const char *optstring = ":clw";

    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    if ((file_src = open(argv[1], O_RDONLY)) < 0) {
        perror("Error ");
        exit(2);
    }

    /* On va lire chaque lettre du fichier 1 par 1 */
    while ((res = read(file_src, &buffer, BUFFER_SIZE)) > 0) {
        if (res == -1) {
            perror("Error ");
            exit(3);
        }

        /* Si c'est un " " :
           Ici on devra peut-être incrémenter le nombre de mot */
        if (strcmp(buffer, " ") == 0) {
            /* Si le dernier caractère était autre chose qu'un espace ou un saut de ligne, on incrémente le nombre de mot */
            if (last_char == IS_A_CHARACTER) {
                nb_mot++;
            }

            last_char = IS_A_SPACE;
        }

        /* Si c'est un "\n" :
           On incrémente le nombre de ligne et peut-être le nombre de mots */
        else if (strcmp(buffer, "\n") == 0) {
            /* De la même façon que précédemment, on incrémente le nombre de mot si et seulement si
               le dernier caractère n'était ni un saut de ligne, ni un espace */
            if (last_char == IS_A_CHARACTER) {
                nb_mot++;
            }

            last_char = IS_A_NEWLINE;

            nb_ligne++;
        }

        /* Sinon, on retient que le dernier caractère est n'est ni un espace, ni un saut de ligne */
        else {
            last_char = IS_A_CHARACTER;
        }

        /* Character */
        nb_char++;
    }
    
    if (last_char == IS_A_CHARACTER) {
        nb_mot++;
    }

    close(file_src);

    /* On va regarder quelles options on va devoir afficher :  
       pour cela, on va remplir le tableau "options" de -1.
       options[i] va être égal à soit le nombre de ligne, de mot ou de caractère.
       Et si options[i] reste égal à -1, ça veut dire qu'on n'avait pas l'option en question */ 
    for (i = 0 ; i < NB_OPTION ; i++) {
        options[i] = -1;
    }

    /* Pour commencer, si on a des options, on les associe à leur case respective du tableau "options" */
    while (EOF != (res = getopt(argc, argv, optstring))) {
		switch(res) { 
		case 'l':
			options[l] = nb_ligne; break;

		case 'w':
			options[w] = nb_mot; break;

		case 'c':
			options[c] = nb_char; break;
		}
	}

    /* Ensuite, on affiche chaque option avec la valeur du tableau qui lui a été associé si options[i] != -1 */
    for (i = 0 ; i < NB_OPTION ; i++) {
        if (options[i] != -1) {
            printf("%d ", options[i]);
            nb_option++; /* Pour rappeler qu'on a bien eu au moins 1 option */
        }
    }

    /* Enfin, on regarde d'abord si on a eu 0 option, dans ce cas là on les affiche toutes.
       Sinon on affiche que le nom du fichier */
    (nb_option == 0) ? printf("%d %d %d %s\n", nb_ligne, nb_mot, nb_char, argv[optind]) :
                       printf("%s\n", argv[optind]);
    
    return EXIT_SUCCESS;
}
