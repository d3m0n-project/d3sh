#include "stdio.hpp"

#define PROGRAM_NAME		"touch"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Create each named file if it does not exist. Existing files are opened without changing their contents."
#define PROGRAM_USAGE		"touch FILE ..."
#define PROGRAM_ARGUMENTS	"FILE - path to create or open; multiple paths are accepted."
#define PROGRAM_EXAMPLES	"touch notes.txt\ntouch one.txt two.txt"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc < 2)
	{
		fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
		return 1;
	}

	int status = 0;
	for (int i = 1; i < argc; i++)
	{
		int fd = open(argv[i], O_WRITE | O_CREATE);
		if (fd < 0)
		{
			fprintf(stderr, "%s: cannot touch %s\n", PROGRAM_NAME, argv[i]);
			status = 1;
		}
		else close(fd);
	}
	return status;
}
