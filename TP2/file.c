#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/* ---------------------------------------------------------- */

void print_struct_file(File *file) {
	FileElement *temp = *file;
	
	while (temp != NULL) {
		printf("%s\n", temp->file_path);
		temp = temp->next;
	}
}

/* ---------------------------------------------------------- */

void push_file(File *file, char *file_path) {
	FileElement *new;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
	FileElement *temp;

	if (*file == NULL) {

		if (NULL == ((*file) = (FileElement*) malloc(sizeof(FileElement*)))) {
			exit(EXIT_FAILURE);
		}

		if (NULL == ((*file)->file_path = (char*) malloc(strlen(file_path) * sizeof(char)))) {
			exit(EXIT_FAILURE);
		}

		strcpy((*file)->file_path, file_path);

		(*file)->next = NULL;
	}

	else {
		new = (FileElement*) malloc(sizeof(FileElement*));

		if (NULL == (new->file_path = (char*) malloc(strlen(file_path) * sizeof(char)))) {
			exit(EXIT_FAILURE);
		}

		strcpy(new->file_path, file_path);
		new->next = NULL;

		temp = (*file);
		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = new;
	}
}

/* ---------------------------------------------------------- */

void free_file(File *file) {
	FileElement *temp = *file;

	while (temp != NULL) {
		(*file) = (*file)->next;
		free(temp->file_path);
		temp->file_path = NULL;
		free(temp);
		temp = NULL;
		temp = (*file);
	}
}

/* ---------------------------------------------------------- */
