#include "stdio.hpp"

#define PROGRAM_NAME "uptime"
#define PROGRAM_AUTHOR "0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc != 1)
	{
		fprintf(stderr, "%s: takes no operands\n", PROGRAM_NAME);
		return 1;
	}
	
	uint32_t seconds = clock() / CLOCKS_PER_SEC;
	printf("up %u seconds\n", seconds);
	return 0;
}
