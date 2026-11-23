#include "stdio.hpp"

#define PROGRAM_NAME		"cp"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Copy one file to another, creating or replacing the destination."
#define PROGRAM_USAGE		"cp SOURCE DESTINATION"
#define PROGRAM_ARGUMENTS	"SOURCE - file to copy.\nDESTINATION - path to create or truncate."
#define PROGRAM_EXAMPLES	"cp notes.txt notes.bak\ncp /tmp/input.txt ./input.txt"
#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc != 3)
	{
		fprintf(stderr, "%s: usage: cp source destination\n", PROGRAM_NAME);
		return 1;
	}
	
	if (strcmp(argv[1], argv[2]) == 0)
	{
		fprintf(stderr, "%s: source and destination are the same file\n", PROGRAM_NAME);
		return 1;
	}

	int in = open(argv[1], O_READ);
	if (in < 0)
	{
		fprintf(stderr, "%s: cannot open %s\n", PROGRAM_NAME, argv[1]);
		return 1;
	}

	int out = open(argv[2], O_WRITE | O_CREATE | O_TRUNC);
	if (out < 0)
	{
		fprintf(stderr, "%s: cannot create %s\n", PROGRAM_NAME, argv[2]);
		close(in);
		return 1;
	}
	char	buf[4096];
	int		n;
	int		status = 0;
	while ((n = read(in, buf, sizeof(buf))) > 0)
	{
		int off = 0;
		while (off < n)
		{
			int written = write(out, buf + off, n - off);
			if (written <= 0)
			{
				status = 1;
				break;
			}
			off += written;
		}
		if (status)
			break;
	}
	if (n < 0)
		status = 1;
	
	close(in);
	close(out);
	if (status)
		fprintf(stderr, "%s: copy failed\n", PROGRAM_NAME);
	
	return status;
}
