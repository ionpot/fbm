#ifndef LIST_H
#define LIST_H

#include "pair.h"

struct List {
	int count;
	struct Pair *buffer;
	struct Pair *lcm;
};

int  list_init(struct List *, int count);
void list_free(struct List *);

int    list_mark(struct List *, long dividend);
void * list_next(struct List *);
void   list_sort(struct List *);

void list_findlcm(struct List *);

void list_print(const struct List *);

#endif
