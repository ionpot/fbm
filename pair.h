#ifndef PAIR_H
#define PAIR_H

struct Pair {
	long number;
	char *text;
	int isdivisor;
};

void pair_init(struct Pair *, long number, char *text);
void pair_parse(struct Pair *, const char *);
void pair_setdivisor(struct Pair *, long);

int  pair_cmp(const struct Pair *, const struct Pair *);
void pair_print(const struct Pair *);

#endif
