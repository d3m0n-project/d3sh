#include "stdio.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		
	}
	else
	{
		fprintf(stderr, "%s: missing operand\n", argv[0]);
		return 1;
	}
}