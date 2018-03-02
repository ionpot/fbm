#include "list.h"
#include "options.h"

#include <assert.h>
#include <stdio.h>

typedef void (*printer)(long);

extern struct Options options;

static void
printnum(long i)
{
	printf("%ld", i);
}

static void
with_list(long i)
{
	int apn = options.always_print_number;

	if (apn)
		printnum(i);

	if (list_mark(i))
		list_print();

	else if (!apn)
		printnum(i);
}

static void
loop(printer f)
{
	long i = 0;

	while (i++ < options.max) {
		if (i > 1)
			putchar(' ');

		f(i);
	}

	putchar('\n');
}

/* export */
void
print_nums(void)
{
	loop(printnum);
}

void
print_list(void)
{
	loop(with_list);
}
