#include "list.h"

#include "pair.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static struct {
	int count;
	struct Pair *buffer;
	struct Pair *lcm;
} list;

static long
calc_gcd(long a, long b)
{
	assert(a > b);
	assert(b != 0);

	if (a == 1) return 1;
	if (b == 1) return 1;

	long rem = a % b;

	return rem
		? calc_gcd(b, rem)
		: b;
}

static long
calc_lcm(long a, long b)
{
	long gcd = (a > b)
		? calc_gcd(a, b)
		: calc_gcd(b, a);

	return (a * b) / gcd;
}

static void
set_first_as_lcm()
{
	list.lcm = list.buffer;
	list.count -= 1;
}

static void
new_lcm_pair(long number)
{
	struct Pair *pair = list.buffer + list.count;

	pair_init(pair, number, NULL);

	list.lcm = pair;
}

static void
find_lcm_pair()
{
	assert(list.count > 1);

	int i = list.count - 1;
	struct Pair *first = list.buffer;
	struct Pair *pair = first + i;
	long lcm = pair->number;

	while (--pair != first)
		lcm = calc_lcm(pair->number, lcm);

	if (first->number == lcm) {
		set_first_as_lcm();

	} else {
		lcm = calc_lcm(first->number, lcm);

		new_lcm_pair(lcm);
	}
}

static struct Pair *
skip_lcm()
{
	int offset = (list.buffer == list.lcm);

	return list.buffer + offset;
}

static int
mark_pairs(long dividend)
{
	struct Pair *pair = skip_lcm();
	int i = list.count;
	int marked = 0;

	for (; i--; pair++) {
		pair_setdivisor(pair, dividend);

		marked += pair->isdivisor;
	}

	return marked;
}

static void
print_divisors()
{
	int i = list.count;
	struct Pair *pair = skip_lcm() + i;

	while (i--) {
		--pair;

		if (pair->isdivisor)
			pair_print(pair);
	}
}

static void
print_pairs()
{
	int i = list.count;
	struct Pair *pair = skip_lcm() + i;

	while (i--)
		pair_print(--pair);
}

static void
print_lcm()
{
	struct Pair *lcm = list.lcm;

	assert(lcm != NULL);

	if (lcm->text == NULL)
		print_pairs();

	else
		pair_print(lcm);
}

/* export */
int
list_init(int count)
{
	assert(count > 0);

	struct Pair *buffer =
		malloc((count + 1) * sizeof(struct Pair));

	list.count = 0;
	list.buffer = buffer;
	list.lcm = buffer + count;

	pair_init(list.lcm, 0, NULL);

	return buffer != NULL;
}

void
list_free()
{
	if (list.buffer != NULL)
		free(list.buffer);
}

void
list_add(long number, const char *text)
{
	assert(number > 0);
	assert(text != NULL);

	struct Pair *pair = list.buffer + list.count;

	pair_init(pair, number, text);
	printf("Pair %ld %s\n", pair->number, pair->text);

	list.count += 1;
}

int
list_count(void)
{
	return list.count;
}

int
list_mark(long dividend)
{
	struct Pair *lcm = list.lcm;

	pair_setdivisor(lcm, dividend);

	return lcm->isdivisor
		? 1
		: mark_pairs(dividend);
}

void
list_sort()
{
	qsort(
		list.buffer,
		list.count,
		sizeof(struct Pair),
		pair_cmp);
}

void
list_findlcm()
{
	assert(list.count > 0);

	switch (list.count) {
	case 1:
		set_first_as_lcm();
		break;

	default:
		find_lcm_pair();
	}

	printf("LCM %ld %s\n", list.lcm->number, list.lcm->text);
}

void
list_print()
{
	struct Pair *lcm = list.lcm;

	assert(lcm != NULL);

	if (lcm->isdivisor)
		print_lcm();

	else
		print_divisors();
}
