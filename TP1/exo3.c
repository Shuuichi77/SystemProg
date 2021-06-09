#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


int main(int argc, char const *argv[]) {
	int i;
	struct dirent *dirEnt;
    DIR *dir;
	struct stat sb;

	/* 0 argument */
	if (argc < 2) {
		/* if (ls_display_file(".", 0) == -1) {
			perror("error\n");
			return EXIT_FAILURE;
		} */

		if ((dir = opendir(".")) == NULL) {
			perror("Cannot open directory\n");
		}

		while ((dirEnt = readdir(dir)) != NULL) {
       		printf("%s\n", dirEnt->d_name);
    	}
	}

	/* Au moins 1 argument */
	else {
		for (i = 1 ; i < argc ; i++) {
			printf("\n|----- %s -----|\n", argv[i]);
			if (stat(argv[1], &sb) == -1) {
				perror("Kolossal erreur sur le fichier\n");
				_exit(2);
			}

			/* argv[1] is a File */
			if (S_ISREG(sb.st_mode)) {
				printf("File : %s\nInode : %lu\nTaille : %ld\nDate de modif. : %sType : f\n", argv[1], sb.st_ino, sb.st_size, ctime(&sb.st_mtime));
			}

			/* argv[1] is a Directory */
			else if (S_ISDIR(sb.st_mode)) {
				if ((dir = opendir(argv[1])) == NULL) {
					perror("Cannot open directory\n");
				}

				while ((dirEnt = readdir(dir)) != NULL) {
	           		printf ("%s (%d)\n", dirEnt->d_name, dirEnt->d_type);
	        	}	
			}

			/* argv[1] is something else */
			else {
				printf("?\n");
			}
		}
	}
	

	return 0;
}