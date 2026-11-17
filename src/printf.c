#include "stdio.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf(argv[1], 0); // TODO: printf
	}
	else
	{
		fprintf(stderr, "%s: not enough arguments\n", argv[0]);
		return 1;
	}
}