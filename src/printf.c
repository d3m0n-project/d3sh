#include "stdio.hpp"

#define PROGRAM_NAME	"printf"
#define PROGRAM_AUTHOR	"0x262d"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf(argv[1], 0); // TODO: printf
	}
	else
	{
		fprintf(stderr, "%s: not enough arguments\n", argv[0]);
		return 1;
	}
}