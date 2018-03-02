#ifndef LIST_H
#define LIST_H

int  list_init(int count);
void list_free();

int  list_count(void);
int  list_mark(long dividend);
void list_add(long num, const char *text);
void list_sort();

void list_findlcm();

void list_print();

#endif
