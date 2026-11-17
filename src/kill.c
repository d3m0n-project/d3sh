#include "stdio.hpp"

#define PROGRAM_NAME "kill"
#define PROGRAM_AUTHOR "0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);

	if (argc != 2)
	{
		fprintf(stderr, "%s: expected a process id\n", PROGRAM_NAME);
		return 1;
	}

	int pid = atoi(argv[1]);
	if (pid <= 0 || kill((uint32_t)pid, 0) != 0)
	{
		fprintf(stderr, "%s: failed to kill process %s\n", PROGRAM_NAME, argv[1]);
		return 1;
	}
	return 0;
}
