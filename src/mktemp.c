#include "stdio.hpp"

#define PROGRAM_NAME "mktemp"
#define PROGRAM_AUTHOR "0x262d"

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	char path[64] = "/tmp/d3sh-000000";
	if (argc > 2)
	{
		fprintf(stderr, "%s: usage: mktemp [template]\n", PROGRAM_NAME);
		return 1;
	}

	if (argc == 2)
	{
		size_t len = strlen(argv[1]);
		if (len >= sizeof(path))
		{
			fprintf(stderr, "%s: template too long\n", PROGRAM_NAME);
			return 1;
		}
		strlcpy(path, argv[1], sizeof(path));
		if (len < 6 || strcmp(path + len - 6, "XXXXXX") != 0)
		{
			fprintf(stderr, "%s: template must end in XXXXXX\n", PROGRAM_NAME);
			return 1;
		}
	}

	static const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int attempt = 0; attempt < 32; attempt++)
	{
		uint32_t random = random_u32();
		for (int i = 0; i < 6; i++)
		{
			path[strlen(path) - 6 + i] = chars[random % 62];
			random = random / 62 + random_u32();
		}

		int fd = open(path, O_WRITE | O_CREATE);
		if (fd >= 0)
		{
			close(fd);
			printf("%s\n", path);
			return 0;
		}
	}
	
	fprintf(stderr, "%s: unable to create temporary file\n", PROGRAM_NAME);
	return 1;
}
