#include "stdio.hpp"
#include "stdlib.h"

#define PROGRAM_NAME			"basename"
#define PROGRAM_AUTHOR			"0x262d"

#define PROGRAM_USAGE			PROGRAM_NAME " NAME"
#define PROGRAM_EXAMPLES		PROGRAM_NAME " path/to/file.ext        -> file.ext\n" \
								PROGRAM_NAME " /programs/bin/lua       -> lua\n" \
								PROGRAM_NAME " /config                 -> config\n"
#define PROGRAM_DESCRIPTION		"Print NAME with any leading directory components removed."

#include "config.h"

#define PROGRAM_ARGUMENTS		PROGRAM_ARGUMENTS_VERSION "\n"

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