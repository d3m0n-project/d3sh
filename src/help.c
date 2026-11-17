#include "stdio.hpp"
#include "stdlib.h"

#define PROGRAM_NAME	"help"
#define PROGRAM_AUTHOR	"0x262d"

#include "config.h"

#ifndef UTILITIES_LIST
	#define UTILITIES_LIST	PROGRAM_NAME
#endif

const char	*UTILITIES[] = {
	UTILITIES_LIST
};

int main(int argc, char **argv)
{
	size_t total_tools = sizeof(UTILITIES)/sizeof(UTILITIES[0]);
	process_version(argc, argv);

	printf("--- d3sh Utilities ---\n");
	for (size_t i=0; i<total_tools; i++)
		printf(" - %s\n", UTILITIES[i]);
	
	printf("\ntotal: %lu tools\n", total_tools);
	printf("version: %s, build: %s\n", D3SH_BUILD_VERSION, D3SH_BUILD_DATE);

	return 0;
}