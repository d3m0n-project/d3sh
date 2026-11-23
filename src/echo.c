#include "stdio.hpp"

#define PROGRAM_NAME		"echo"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Print words separated by spaces and a newline; -n suppresses the trailing newline."
#define PROGRAM_USAGE		"echo [-n] [STRING ...]"
#define PROGRAM_ARGUMENTS	"-n - suppress the trailing newline.\nSTRING - text to print."
#define PROGRAM_EXAMPLES	"echo hello world\necho -n ready"

#include "config.h"


int main(int argc, char **argv)
{
	process_version(argc, argv);
	int i = 1;
	if (i < argc && strcmp(argv[i], "-n") == 0)
		i++;
	
	for (; i < argc; i++)
		printf("%s%s", i == 1 || (i == 2 && strcmp(argv[1], "-n") == 0) ? "" : " ", argv[i]);
	
	if (!(argc > 1 && strcmp(argv[1], "-n") == 0))
		printf("\n");
	
	return 0;
}
