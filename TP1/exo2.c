#define _DEFAULT_SOURCE
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
	struct stat sb;
	char buffer[255];
	int buffer_size = 255;
	
	if (argc != 2) {
		fprintf(stderr, "Erreur : aucun fichier n'a été fourni\n");
		_exit(1);
	}

	if (lstat(argv[1], &sb) == -1) {
		perror("Kolossal erreur sur le fichier\n");
		_exit(2);
	}

	printf("File : %s\nInode : %lu\nTaille : %ld octet(s) \nDate de modif. : %sType : ", argv[1], sb.st_ino, sb.st_size, ctime(&sb.st_mtime));

	if (S_ISLNK(sb.st_mode)) {
		readlink(argv[1], buffer, buffer_size);
		printf("l (%s -> %s)\n", argv[1], buffer);
	}

	else if (S_ISDIR(sb.st_mode)) {
		printf("d\n");
	}

	else if (S_ISREG(sb.st_mode)) {
		printf("f\n");
	}

	else {
		printf("?\n");
	}

	return 0;
}