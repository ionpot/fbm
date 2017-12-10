#include "list.h"

#include <stdio.h>
#include <stdlib.h>

static struct List list;
static void (*printnum)(long) = NULL;

static void
print_usage(char *name)
{
	puts("Usage:");
	printf("%s <until> [<pair>]...\n", name);
	puts("<until> ::= <digit>+");
	puts("<pair> ::= <digit>+<word>+");
	puts("Example:");
	printf("%s 100 3fizz 5buzz\n", name);
	puts(
		"This will loop from 1 to 100 (inclusive),"
		" substituting the numbers divisible by 3 with \"fizz\","
		" 5 with \"buzz\", 15 with \"fizzbuzz\".");
}

static void
print_nolist(long i)
{
	printf("%l", i);
}

static void
print_list(long i)
{
	if (list_mark(&list, i))
		list_print(&list);

	else
		printf("%l", i);
}

static void
begin(long max)
{
	assert(printnum != NULL);

	long i = 0;

	while (i++ < max) {
		if (i > 1)
			putchar(' ');

		printnum(i);
	}
}

static int
init_list(int argc, const char **argv)
{
	assert(argc > 0);
	assert(argv != NULL);

	int ok = list_init(&list, argc);

	if (ok) {
		while (argc--)
			list_add(&list, argv[argc]);

		list_sort(&list);
		list_findlcm(&list);
	}

	return ok;
}

static int
init(int argc, const char **argv)
{
	int ok = 1;

	if (argc) {
		ok = init_list(argc, argv);

		if (ok)
			printnum = print_list;

	} else {
		printnum = print_nolist;
	}

	return ok;
}

static void
cleanup(void)
{
	if (printnum == print_list)
		list_free(&list);
}

int
main(int argc, char **argv)
{
	long max;

	if (argc > 1) {
		max = atoi(argv[1]);

		if (init(argc - 2, argv + 2)) {
			begin(max);
			cleanup();
		}

	} else {
		print_usage(argv[0]);
	}

	return 0;
}
