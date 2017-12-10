#include "list.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

static long
find_gcd(long a, long b)
{
	assert(a > b);
	assert(b != 0);

	if (a == 1) return 1;
	if (b == 1) return 1;

	long rem = a % b;

	return rem
		? find_gcd(b, rem)
		: b;
}

static long
find_lcm(struct List *list)
{
	assert(list != NULL);
	assert(list->count > 1);

	int i = list->count - 1;
	struct Pair *pair = list->buffer + i;
	long num = pair->number;
	long mult = num;
	long gcd = num;

	while (i--) {
		--pair;

		num = pair->number;

		assert(num > 0);

		mult *= num;
		gcd = find_gcd(num, gcd);
	}

	return mult / gcd;
}

static void
setlcm_tofirst(struct List *list)
{
	assert(list != NULL);

	list->lcm = list->buffer;
	list->count -= 1;
}

static struct Pair *
skip_lcm(const struct List *list)
{
	assert(list != NULL);

	int offset = (list->buffer != list->lcm);

	return list->buffer + offset;
}

static int
mark_pairs(struct List *list, long dividend)
{
	assert(list != NULL);

	struct Pair *pair = skip_lcm(list);
	int i = list->count;
	int marked = 0;

	for (; i--; pair++) {
		pair_setdivisor(pair, dividend);

		marked += pair->isdivisor;
	}

	return marked;
}

static void
print_divisors(const struct List *list)
{
	assert(list != NULL);

	int i = list->count;
	struct Pair *pair = skip_lcm(list) + i;

	while (i--) {
		--pair;

		if (pair->isdivisor)
			pair_print(pair);
	}
}

static void
print_pairs(const struct List *list)
{
	assert(list != NULL);

	int i = list->count;
	struct Pair *pair = skip_lcm(list) + i;

	while (i--)
		pair_print(--pair);
}

static void
print_lcm(const struct List *list)
{
	assert(list != NULL);

	struct Pair *lcm = list->lcm;

	assert(lcm != NULL);

	if (lcm->text == NULL)
		print_pairs(list);

	else
		pair_print(lcm);
}

/* export */
int
list_init(struct List *list, int count)
{
	assert(list != NULL);
	assert(count > 0);

	struct Pair *buffer =
		malloc((count + 1) * sizeof(struct Pair));

	list->count = 0;
	list->buffer = buffer;
	list->lcm = buffer + count;

	pair_init(list->lcm, 0, NULL);

	return buffer != NULL;
}

void
list_free(struct List *list)
{
	assert(list != NULL);

	if (list->buffer != NULL)
		free(list->buffer);
}

void
list_add(struct List *list, const char *raw)
{
	assert(list != NULL);
	assert(raw != NULL);

	struct Pair *pair = list->buffer + list->count;

	pair_parse(pair, raw);

	if (pair->number)
		list->count += 1;
}

int
list_mark(struct List *list, long dividend)
{
	assert(list != NULL);

	struct Pair *lcm = list->lcm;

	pair_setdivisor(lcm, dividend);

	return lcm->isdivisor
		? 1
		: mark_pairs(list, dividend);
}

void
list_sort(struct List *list)
{
	assert(list != NULL);

	qsort(
		list->buffer,
		list->count,
		sizeof(struct Pair),
		pair_cmp);
}

void
list_findlcm(struct List *list)
{
	assert(list != NULL);
	assert(list->count > 0);

	struct Pair *first = list->buffer;

	switch (list->count) {
	case 1:
		setlcm_tofirst(list);
		break;

	default:
		pair_init(list->lcm, find_lcm(list), NULL);

		if (!pair_cmp(list->lcm, first))
			setlcm_tofirst(list);
	}
}

void
list_print(const struct List *list)
{
	assert(list != NULL);

	struct Pair *lcm = list->lcm;

	assert(lcm != NULL);

	if (lcm->isdivisor)
		print_lcm(list);

	else
		print_divisors(list);
}
