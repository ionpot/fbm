#include "args.h"
#include "list.h"
#include "options.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern struct Options options;

extern void usage_print(void);

static struct List list;
static void (*printnum)(long) = NULL;

static void
print_nolist(long i)
{
	printf("%ld", i);
}

static void
print_list(long i)
{
	int apn = options.always_print_number;

	if (apn)
		printf("%ld", i);

	if (list_mark(&list, i))
		list_print(&list);

	else if (!apn)
		printf("%ld", i);
}

static void
begin(void)
{
	if (!options.max)
		goto no_max;

	if (list.count) {
		list_sort(&list);
		list_findlcm(&list);

		printnum = print_list;

	} else {
		printnum = print_nolist;
	}

	long i = 0;

	while (i++ < options.max) {
		if (i > 1)
			putchar(' ');

		printnum(i);
	}

	putchar('\n');

	return;

no_max:
	puts("No max provided.");
}

int
main(int argc, char **argv)
{
	if (argc > 1) {
		if (list_init(&list, argc - 1)) {
			args_parse(argc, argv, &list);
			begin();
			list_free(&list);
		}

	} else {
		usage_print();
	}

	return 0;
}
