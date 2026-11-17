#include "stdio.hpp"

#define PROGRAM_NAME	"uname"
#define PROGRAM_AUTHOR	"0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		(void)argv;
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}
}