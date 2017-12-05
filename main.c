#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct Pair {
	long number;
	char *text;
};

static struct {
	long max;
	long pair_count;
} options;

static struct {
	size_t size;
	char *buffer;
	char *head;
} line;

static struct Pair *list;

void print_line(long i)
{
	long matches = seek_pairs(i);

	line_clear();

	if (matches)
		line_print();

	else
		printf("%l\n", i);
}

int init()
{
	line_init();

	return 0;
}

int begin()
{
	long i = 0;

	while (i < options.max)
		print_line(++i);

	return 0;
}

int main(int argc, char **argv)
{
	return init(argc, argv) && begin();
}
