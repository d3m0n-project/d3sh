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

#endif