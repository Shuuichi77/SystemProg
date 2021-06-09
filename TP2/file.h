#ifndef FILE_H
#define FILE_H

/* ---------------------------------------------------------- */

	/**
	 * Structure de la pile qu'on utilisera pour le TP 
	 */
	typedef struct FileElement {
		char *file_path;
		struct FileElement *next;
	} FileElement, *File;

/* ---------------------------------------------------------- */

	void print_struct_file(File *file);

	/* Ajoute un élément à la pile chaînée avec les valeurs "x" et "y" prises en paramètres */
	void push_file(File *file, char *file_path);

	/* Libère la mémoire allouée à tous les éléments de la pile chaînée */
	void free_file(File *file);

/* ---------------------------------------------------------- */

#endif