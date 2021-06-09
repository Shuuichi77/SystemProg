#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "ls.h"

int main(int argc, char * const argv[]) {
	int options[4] = {0}, val;
	const char *optstring = ":lnRa";

	while (EOF != (val = getopt(argc, argv, optstring))) {
		switch(val) { 
		case 'l':
			options[l] = 1; break;

		case 'n':
			options[n] = 1; break;

		case 'R':
			options[R] = 1; break;

		case 'a':
			options[a] = 1; break;

		case '?':
			printf("unknown option %c\n", optopt); break;
		}
	}

	if (argc < 2 || optind == argc) {
		if (display_directory("./", options) == -1) {
			return EXIT_FAILURE;
		}
	}

	for( ; optind < argc ; optind++) {
		if (display_directory(argv[optind], options) == -1) {
			return EXIT_FAILURE;
		}

		printf("\n");
	}


	return 0;
}