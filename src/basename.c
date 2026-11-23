#include "stdio.hpp"
#include "stdlib.h"

#define PROGRAM_NAME			"basename"
#define PROGRAM_AUTHOR			"0x262d"
#define PROGRAM_DESCRIPTION		"Print a path with its leading directory components removed."
#define PROGRAM_USAGE			"basename NAME"
#define PROGRAM_ARGUMENTS		"NAME - path whose final component is printed."
#define PROGRAM_EXAMPLES		"basename path/to/file.txt      -> file.txt\n" \
								"basename /programs/bin/lua     -> prints lua"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc > 1)
	{
		char *name = argv[1];
		size_t i = strlen(name) - 1;
		while (i > 0 && name[i] != '/')
			i--;
		printf("%s\n", name + i);
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}
}
