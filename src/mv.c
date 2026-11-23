#include "stdio.hpp"

#define PROGRAM_NAME		"mv"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Move or rename a path to a destination."
#define PROGRAM_USAGE		"mv SOURCE DESTINATION"
#define PROGRAM_ARGUMENTS	"SOURCE - existing path to move.\nDESTINATION - new path."
#define PROGRAM_EXAMPLES	"mv draft.txt final.txt\nmv report.txt /tmp/report.txt"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc != 3)
	{
		fprintf(stderr, "%s: usage: mv source destination\n", PROGRAM_NAME);
		return 1;
	}

	if (rename(argv[1], argv[2]) != 0)
	{
		fprintf(stderr, "%s: cannot move %s to %s\n", PROGRAM_NAME, argv[1], argv[2]);
		return 1;
	}
	return 0;
}
