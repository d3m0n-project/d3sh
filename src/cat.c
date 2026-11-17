#include "stdio.hpp"
#include "sys.h"

#define PROGRAM_NAME	"cat"
#define PROGRAM_AUTHOR	"0x262d"

#include "config.h"

#define READ_CHUNK_SIZE	4096

bool	cat_file(int fd)
{
	if (fd < 0)
		return false;

	size_t	read_size = 0;
	char	read_buf[READ_CHUNK_SIZE] = {0};
	while ((read_size = read(fd, read_buf, READ_CHUNK_SIZE)) > 0)
		write(1, read_buf, read_size);
	
	if (fd > 0)
		close(fd);
	return true;
}

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc > 1)
	{
		bool worked = false;
		for (int i=1; i<argc; i++)
		{
			bool result = cat_file(open(argv[i], O_READ));
			if (!result)
				fprintf(stderr, "%s: %s: No such file or directory\n", PROGRAM_NAME, argv[1]);
			worked |= result;
		}
		return !worked;
	}
	else
	{
		while (1)
			cat_file(0);
		return 0;
	}
	return 0;
}