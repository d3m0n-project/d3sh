#include "stdio.hpp"

#define PROGRAM_NAME	"rm"
#define PROGRAM_AUTHOR	"0x262d"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}
}