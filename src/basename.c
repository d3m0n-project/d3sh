#include "stdio.hpp"
#include "stdlib.h"

#define PROGRAM_NAME	"basename"
#define PROGRAM_AUTHOR	"0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char *name = argv[1];
		size_t i = strlen(name) - 1;
		while (i > 0 && name[i] != '/')
			i--;
		printf("%s\n", name + i + 1);
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}
}