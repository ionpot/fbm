#ifndef DEBUG_H
#define DEBUG_H

#include "options.h"

#include <stdio.h>

#define debug(M, ...) \
	if (options.print_debug_info)\
		fprintf(stderr, M "\n", ##__VA_ARGS__)

#endif
