#include "stdio.hpp"
#include "stdlib.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char *name = argv[1];
		size_t i = strlen(name) - 1;
		while (i > 0 && name[i] != '/')
			i--;
		printf("%s\n", name);
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", argv[0]);
		return 1;
	}
}