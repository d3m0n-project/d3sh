#include "stdio.hpp"

#define PROGRAM_NAME		"uname"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Print system information. Options -s and -a are accepted and currently return the same information."
#define PROGRAM_USAGE		"uname [-s | -a]"
#define PROGRAM_ARGUMENTS	"-s - request the system name.\n-a - request all available system information."
#define PROGRAM_EXAMPLES	"uname\nuname -s\nuname -a"
#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc > 2 || (argc == 2 && strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-s") != 0))
	{
		fprintf(stderr, "%s: supported options are -s and -a\n", PROGRAM_NAME);
		return 1;
	}

	char info[128] = {0};
	if (uname(info, sizeof(info)) != 0)
	{
		fprintf(stderr, "%s: system information unavailable\n", PROGRAM_NAME);
		return 1;
	}
	printf("%s\n", info);
	return 0;
}
