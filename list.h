#ifndef LIST_H
#define LIST_H

#include "pair.h"

struct List {
	int count;
	struct Pair *buffer;
	long lcm;
};

void list_init(struct List *, int count, char **argv);
void list_free(struct List *);

int list_mark(struct List *, long dividend);

void list_print(const struct List *);

#endif
