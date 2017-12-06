#include "pair.h"

#include <stdio.h>
#include <stdlib.h>

static struct {
	long max;
	long pair_count;
} options;

static struct Pair *list;

void
print_usage(char *name)
{
	puts("Usage:");
	printf("%s until [pair]...\n", name);
	puts("until ::= <int>");
	puts("pair ::= <int><text>");
	puts("Example:");
	printf("%s 100 3fizz 5buzz\n", name);
	puts(
		"This will loop from 1 to 100 (inclusive),"
		" substituting the numbers divisible by 3 with \"fizz\","
		" 5 with \"buzz\", 15 with \"fizzbuzz\".");
}

void
print_divisors(void)
{
}

int
mark_divisors(long i)
{
}

void print_line(long i)
{
	int marked = mark_divisors(i);

	if (marked)
		print_divisors();

	else
		printf("%l", i);

	putchar('\n');
}

void
set_max(char *input)
{
	options.max = atoi(input);
}

void
init_pairs(int count, char **argv)
{
}

void
begin(void)
{
	long i = 0;

	while (i < options.max)
		print_line(++i);
}

int main(int argc, char **argv)
{
	switch (argc) {
	case 1:
		print_usage(argv[0]);
		break;
	case 2:
		set_max(argv[1]);
		begin();
		break;
	default:
		set_max(argv[1]);
		init_pairs(argc - 2, argv + 2);
		begin();
		break;
	}

	return 0;
}
