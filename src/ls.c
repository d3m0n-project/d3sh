#include "stdio.hpp"

#define PROGRAM_NAME "ls"
#define PROGRAM_AUTHOR "0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc > 2)
	{
		fprintf(stderr, "%s: accepts one directory\n", PROGRAM_NAME);
		return 1;
	}

	const char *path = argc == 2 ? argv[1] : ".";
	char *entries[128] = {0};
	int count = getdents(path, entries, sizeof(entries));
	if (count < 0)
	{
		fprintf(stderr, "%s: cannot read directory %s\n", PROGRAM_NAME, path);
		return 1;
	}

	for (int i = 0; i < count && i < 128; i++)
		if (entries[i])
			printf("%s\n", entries[i]);
	return 0;
}
