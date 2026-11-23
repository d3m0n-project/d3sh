#include "stdio.hpp"

#define PROGRAM_NAME		"printf"
#define PROGRAM_AUTHOR		"0x262d"
#define PROGRAM_DESCRIPTION	"Print formatted text without a newline. Supports %s, %d, %i, %c, and %% conversions."
#define PROGRAM_USAGE		"printf FORMAT [ARGUMENT ...]"
#define PROGRAM_ARGUMENTS	"FORMAT - text containing supported conversions.\nARGUMENT - value consumed by a conversion."
#define PROGRAM_EXAMPLES	"printf \"Hello, %s!\\n\" world\nprintf \"%d + %d = %d\\n\" 2 3 5\nprintf \"100%%\\n\""

#include "config.h"

int main(int argc, char **argv)
{
	process_version(argc, argv);
	if (argc < 2)
	{
		fprintf(stderr, "%s: missing format operand\n", PROGRAM_NAME);
		return 1;
	}

	const char *fmt = argv[1];
	int arg = 2;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			putchar_fd(*fmt++, 1);
			continue;
		}
		fmt++;

		if (*fmt == '%')							{ putchar_fd('%', 1); fmt++; continue; }
		if (!*fmt)									{ putchar_fd('%', 1); break; }

		if (arg >= argc) { arg = 2; }

		if (*fmt == 's')							putstr_fd(arg < argc ? argv[arg] : "", 1);
		else if (*fmt == 'd' || *fmt == 'i')		putnbr_fd(arg < argc ? atoi(argv[arg]) : 0, 1);
		else if (*fmt == 'c')						putchar_fd(arg < argc ? argv[arg][0] : '\0', 1);
		else {										putchar_fd('%', 1); putchar_fd(*fmt, 1); fmt++; continue; }

		if (arg < argc)
			arg++;
		fmt++;
	}
	return 0;
}
