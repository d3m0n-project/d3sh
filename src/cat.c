#include "stdio.hpp"
#include "sys.h"

#define PROGRAM_NAME	"cat"
#define PROGRAM_AUTHOR	"0x262d"

int main(int argc, char **argv)
{
	int fd = 0;
	if (argc > 1)
	{
		fd = open(argv[1], O_READ);
		if (fd <= 0)
		{
			return 1;
		}
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}
}