#include "pair.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int
pair_cmp(
	const struct Pair *a,
	const struct Pair *b)
{
	assert(a != NULL);
	assert(b != NULL);

	long na = a->number;
	long nb = b->number;

	return (na < nb) - (na > nb);
}

void
pair_parse(struct Pair *pair, const char *raw)
{
	assert(pair != NULL);
	assert(raw != NULL);

	pair->number = strtol(raw, &pair->text, 10);
	pair->isdivisor = 0;
}

void
pair_print(const struct Pair *pair)
{
	assert(pair != NULL);

	printf("%s", pair->text);
}

void
pair_setdivisor(struct Pair *pair, long i)
{
	assert(pair != NULL);

	pair->isdivisor = !(i % pair->number);
}
