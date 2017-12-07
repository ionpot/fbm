#include "list.h"

#include <stdio.h>
#include <stdlib.h>

static struct List list;

void
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

void
print_number(long i)
{
	int marked = list_mark(&list, i);

	if (marked)
		list_print(&list);

	else
		printf("%l", i);

	putchar(' ');
}

void
begin(long max)
{
	long i = 0;

	while (i < max)
		print_number(++i);
}

int
main(int argc, char **argv)
{
	long max;

	if (argc > 1) {
		max = atoi(argv[1]);

		if (argc > 2)
			list_init(&list, argc - 2, argv + 2);

		begin(max);

	} else {
		print_usage(argv[0]);
	}

	return 0;
}
