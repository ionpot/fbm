#include "args.h"

#include "list.h"
#include "options.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern struct Options options;

static void
parse_pair(const char *arg, struct List *list)
{
	assert(arg != NULL);

	char *text;
	long num = strtol(arg, &text, 10);

	if (num) {
		if (*text == '\0')
			options.max = num;

		else
			list_add(list, num, text);

	} else {
		printf("Ignoring: %s\n", arg);
	}
}

static void
parse_arg(const char *arg, struct List *list)
{
	assert(arg != NULL);

	if (*arg == '-')
		options_parse(arg + 1);

	else
		parse_pair(arg, list);
}

/* export */
void
args_parse(int argc, char **argv, struct List *list)
{
	assert(argv != NULL);

	if (--argc) {
		parse_arg(argv[argc], list);
		args_parse(argc, argv, list);
	}
}
