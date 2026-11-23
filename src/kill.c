#include "stdio.hpp"

#define PROGRAM_NAME "kill"
#define PROGRAM_AUTHOR "0x262d"
#define PROGRAM_DESCRIPTION "Check whether a process can be signaled by sending signal 0. This utility does not currently select a terminating signal."
#define PROGRAM_USAGE "kill PID"
#define PROGRAM_ARGUMENTS "PID - positive process ID to check."
#define PROGRAM_EXAMPLES "kill 42"

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
