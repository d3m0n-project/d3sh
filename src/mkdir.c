#include "stdio.hpp"

#define PROGRAM_NAME		"mkdir"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Create one or more directories."
#define PROGRAM_USAGE		"mkdir DIRECTORY ..."
#define PROGRAM_ARGUMENTS	"DIRECTORY - directory path to create; multiple paths are accepted."
#define PROGRAM_EXAMPLES	"mkdir reports\nmkdir src include docs"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc < 2)
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}

	int status = 0;
	for (int i = 1; i < argc; i++)
	{
		if (mkdir(argv[i]) != 0)
		{
			fprintf(stderr, "%s: cannot create directory %s\n", PROGRAM_NAME, argv[i]);
			status = 1;
		}
	}
	return status;
}
