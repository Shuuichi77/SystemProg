#ifndef LS_H
#define LS_H

/* -------------------------------------------------------- */
	
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
	#include "file.h"

	enum options {
		l,
		n, 
		R,
		a
	};

/* -------------------------------------------------------- */

	void ls_get_perm(struct stat sb, char *perm);
	
	int print_file(const char *path, char *file_name, char *perm, int *options, File *sub_directories);

	int isDirectory(const struct dirent* dirent);

	int display_directory(const char *path, int *options);

	int display_subdirectories(File file, int *options);

/* -------------------------------------------------------- */

#endif