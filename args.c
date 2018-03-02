#include "args.h"

#include "list.h"
#include "options.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern struct Options options;

static void
parse_pair(const char *arg)
{
	assert(arg != NULL);

	char *text;
	long num = strtol(arg, &text, 10);

	if (num) {
		if (*text == '\0')
			options.max = num;

		else
			list_add(num, text);

	} else {
		printf("Ignoring: %s\n", arg);
	}
}

static void
parse_arg(const char *arg)
{
	assert(arg != NULL);

	if (*arg == '-')
		options_parse(arg + 1);

	else
		parse_pair(arg);
}

/* export */
void
args_parse(int argc, char **argv)
{
	assert(argv != NULL);

	if (--argc) {
		parse_arg(argv[argc]);
		args_parse(argc, argv);
	}
}
