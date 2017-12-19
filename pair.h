#ifndef PAIR_H
#define PAIR_H

struct Pair {
	long number;
	const char *text;
	int isdivisor;
};

void pair_init(struct Pair *, long, const char *);
void pair_parse(struct Pair *, const char *);
void pair_setdivisor(struct Pair *, long);

int  pair_cmp(const void *, const void *);
void pair_print(const struct Pair *);

#endif
