#ifndef LINE_H
#define LINE_H

#include <stddef.h>

struct Line {
	size_t size;
	char *buffer;
	char *head;
};

int  line_init(struct Line *, size_t size);
void line_free(struct Line *);

void line_clear(struct Line *);
void line_write(struct Line *, char *);

void line_print(struct Line *);

#endif
