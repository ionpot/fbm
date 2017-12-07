#include "list.h"

#include <assert.h>
#include <stddef.h>

static void
populate(struct List *list, int count, char **argv)
{
}

void
list_init(struct List *list, int count, char **argv)
{
	assert(list != NULL);
	assert(count > 0);
	assert(argv != NULL);

	struct Pair *buffer = malloc(count * sizeof(struct Pair));

	list->buffer = buffer;
	list->count = 0;
	list->lcm = 0;

	if (buffer != NULL)
		populate(list, count, argv);
}

void
list_free(struct List *list)
{
	assert(list != NULL);

	if (list->buffer != NULL)
		free(list->buffer);
}

int
list_mark(struct List *list, long dividend)
{
	assert(list != NULL);

	struct Pair *pair;
	int marked = 0;
	int i = 0;

	for (; i < list->count; i++) {
		pair = list->buffer + i;

		pair_setdivisor(pair, dividend);

		marked += pair->isdivisor;

		if (pair->number == list->lcm)
			if (pair->isdivisor)
				break;
	}

	return marked;
}

void
list_print(const struct List *)
{
}
