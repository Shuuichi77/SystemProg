#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include "ls.h"

/* -------------------------------------------------------- */

void ls_get_perm(struct stat sb, char *perm) {
	unsigned int i;
	struct _permmap 
	{
		char perm;
		int value;
	} permmap[] = {
		{'r', S_IRUSR & sb.st_mode},
		{'w', S_IWUSR & sb.st_mode},
		{'x', S_IXUSR & sb.st_mode},
		{'r', S_IRGRP & sb.st_mode},
		{'w', S_IWGRP & sb.st_mode},
		{'x', S_IXGRP & sb.st_mode},
		{'r', S_IROTH & sb.st_mode},
		{'w', S_IWOTH & sb.st_mode},
		{'x', S_IXOTH & sb.st_mode},
	};

	for (i = 0U ; i < 9U ; ++i) {
		if (permmap[i].value > 0) {
			perm[i] = permmap[i].perm;
		}

		else {
			perm[i] = '-';
		}
	}

	perm[9] = '\0';
}

/* -------------------------------------------------------- */

int print_file(const char *path, char *file_name, char *perm, int *options, File *sub_directories) {
	struct stat sb;
	char *file_path = NULL, *slash = "/";

	/* If we don't have -a, we don't print "." and ".." */
	if (!options[a]) {
		if (strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0) {
			return 1;
		}
	}

	/* If we don't have -n, -l nor -R, we just print the file */
	if (!options[n] && !options[l] && !options[R]) {
		printf("%s ", file_name);
	}

	else {
		if (path[strlen(path) - 1] != '/') {
			if (NULL == (file_path = (char *) malloc((strlen(path) + 1 + strlen(file_name)) * sizeof(char)))) {
				return -1;
			}

			strcpy(file_path, path);
			strcat(file_path, slash);
			strcat(file_path, file_name);
		}

		else {
			if (NULL == (file_path = (char *) malloc((strlen(path) + strlen(file_name)) * sizeof(char)))) {
				return -1;
			}

			strcpy(file_path, path);
			strcat(file_path, file_name);
		}

		if (stat(file_path, &sb) == -1) {
			perror("Path doesn't exist");
			return -2;
		}

		if (options[n]) {
			ls_get_perm(sb, perm);
			printf("%c%s %ld %d %d %9ld %.19s %s\n", S_ISDIR(sb.st_mode) ? 'd' : '-',
		       											     perm,
		       											     sb.st_nlink,
		       										   		 sb.st_uid,
		       										   		 sb.st_gid,
		       										   		 sb.st_size,
		       										   		 ctime(&sb.st_mtime),
		       										   		 file_name);
		}

		else if (options[l]) {
			ls_get_perm(sb, perm);
			printf("%c%s %ld %s %s %9ld %.19s %s\n", S_ISDIR(sb.st_mode) ? 'd' : '-',
		       											     perm,
		       											     sb.st_nlink,
		       											     getpwuid(sb.st_uid)->pw_name,
		       											     getgrgid(sb.st_gid)->gr_name,
		       											     sb.st_size,
		       											     ctime(&sb.st_mtime), /* %.19s to cut the "\n" */
		       											     file_name);
		}

		else {
			printf("%s ", file_name);
		}

		/* We add the file path if it's a directory, and it's different of "." and ".." */
		if (S_ISDIR(sb.st_mode) && options[R] && strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0) {
			push_file(sub_directories, file_path);
		}

		free(file_path);
		file_path = NULL;
	}

	return 1;
}

/* -------------------------------------------------------- */

int isDirectory(const struct dirent* dirent) {
	return dirent->d_type == DT_DIR;
}

/* -------------------------------------------------------- */

int display_directory(const char *path, int *options) {
	File sub_directories = NULL;
	struct dirent **namelist;
    int n, i;
	struct stat sb;
	char perm[9];

	if (stat(path, &sb) == -1) {
		printf("(%s) ", path);
		perror("Couldn't find path ");
		return -1;
	}

	/* If it's a File */
	if (S_ISREG(sb.st_mode)) {
		printf("File : %s\nInode : %lu\nTaille : %ld\nDate de modif. : %sType : f\n", path, sb.st_ino, sb.st_size, ctime(&sb.st_mtime));
		return 1;
	}

	/* If it's a Directory */
	else if (S_ISDIR(sb.st_mode)) {
		n = scandir(path, &namelist, 0, alphasort);

		if (n < 0) {
        	perror("scandir");
        	return -1;
    	}

    	else {
    		if (options[R]) {
    			printf("%s:\n", path);
    		}

    		for (i = 0 ; i < n ; i++) {
	       		if (print_file(path, namelist[i]->d_name, perm, options, &sub_directories) < 0) {
	       			return -1;
	       		}

	       		free(namelist[i]);
	    	}
    	}

    	free(namelist);
    	printf("\n");
    }

    if (options[R]) {
    	if (display_subdirectories(sub_directories, options) < 0) {
    		return -1;
    	}

    	free_file(&sub_directories);
    }

	return 1;
}

/* -------------------------------------------------------- */

int display_subdirectories(File file, int *options) {
	FileElement *temp = file;

	while (temp != NULL) {
		printf("\n");

		if (display_directory(temp->file_path, options) < 0) {
			return -1;
		}
		temp = temp->next;
	}

	return 1;
}

/* -------------------------------------------------------- */