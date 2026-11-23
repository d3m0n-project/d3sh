#ifndef CONFIG_H
#define CONFIG_H

#include "sys.h"
#include "stdio.hpp"
#include "version.h"

#ifndef D3SH_BUILD_VERSION
	#define D3SH_BUILD_VERSION	"1.0.0"
	#define D3SH_BUILD_DATE		"17/11/2026 12:27 GMT"
#endif

#ifndef PROGRAM_NAME
	#define PROGRAM_NAME		"unknown_program"
#endif

#define process_version(argc, argv)		{if (argc > 1 && (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))) {\
	printf("%s version: %s, build: %s\n", PROGRAM_NAME, D3SH_BUILD_VERSION, D3SH_BUILD_DATE); \
	exit(0); \
}}
#define PROGRAM_ARGUMENTS_VERSION	 "-v, --version     print version"

// dummy macros, will be read by docs build script
#ifndef PROGRAM_USAGE
	#define PROGRAM_USAGE			""
#endif
#ifndef PROGRAM_EXAMPLES
	#define PROGRAM_EXAMPLES			""
#endif
#ifndef PROGRAM_DESCRIPTION
	#define PROGRAM_DESCRIPTION		"unknown program"
#endif
#ifndef PROGRAM_ARGUMENTS
	#define PROGRAM_ARGUMENTS		PROGRAM_ARGUMENTS_VERSION
#endif

#endif