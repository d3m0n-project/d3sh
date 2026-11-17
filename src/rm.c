#include "stdio.hpp"

#define PROGRAM_NAME "rm"
#define PROGRAM_AUTHOR "0x262d"

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
		if (remove(argv[i]) != 0)
		{
			fprintf(stderr, "%s: cannot remove %s\n", PROGRAM_NAME, argv[i]);
			status = 1;
		}
	}
	return status;
}
